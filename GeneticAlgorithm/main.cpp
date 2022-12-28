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
    GeneticAlgorithm *ga = new GeneticAlgorithm(2, 50, 1000, function_ptr);
    //ga->setMutationUniform();
    ga->setElite(2);
    //ga->setMutationProb(0.1);
    ga->setMaxChromosome(0, 100);
    //ga->setMinChromosome(1, 100);
    ga->setMaxChromosome(1, 100);
    ga->setStopCriteria(0.);
    ga->evolution();
    delete(ga);
    cout<<"FIM"<<endl;
    return 0;
}


