#include <iostream>
#include <vector>
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "HillClimbing/HillClimbing.h"

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
    ga->setMaxParameter(0, 100);
    //ga->setMinParameter(1, 100);
    ga->setMaxParameter(1, 100);
    ga->setStopCriteria(0.0003);
    ga->search();
    delete(ga);
    cout<<"FIM AG"<<endl;
    HillClimbing *hc = new HillClimbing(2, 1000, function_ptr);
    hc->setNoise(0.1);
    hc->search();
    return 0;
}


