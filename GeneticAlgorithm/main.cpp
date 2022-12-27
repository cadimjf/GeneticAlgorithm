#include <iostream>
#include <vector>
#include "GeneticAlgorithm.h"
using namespace std;

double myFunction(double x, double y){
    return x*x + x*y -y + 5.0;
}
double myFitness(vector<double> param){
    double res = myFunction(param.at(0), param.at(1));
    return fabs(res);
}

int main() {
    double (*function_ptr)(vector<double>) = &myFitness;
    //(*function_ptr)()
    GeneticAlgorithm *ga = new GeneticAlgorithm(2, 50, 100, function_ptr);
    //ga->setMutationProb(0.1);
    ga->setElite(0);
    std::cout << "Hello, World!er" << std::endl;
    ga->setMaxAllele(0, 100);
    //ga->setMinAllele(1, 100);
    ga->setMaxAllele(1, 100);
    ga->evolution();
    delete(ga);
    cout<<"apaguei memo"<<endl;
    return 0;
}


