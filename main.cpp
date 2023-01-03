#include <iostream>
#include <vector>
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "HillClimbing/HillClimbing.h"
#include "SimulatedAnnealing/SimulatedAnnealing.h"
using namespace std;

double myFunction(double x, double y){
    return -x*x + x*y -y + 5.0;
}
double myFitness(vector<double> param){
    double res = myFunction(param.at(0), param.at(1));
    return fabs(res);
}
void run(){
    int iterations = 1000000;
    double stopCriteria = 1e-6;
    double (*function_ptr)(vector<double>) = &myFitness;
    int numParameter = 2;
    //(*function_ptr)()
    GeneticAlgorithm *ga = new GeneticAlgorithm(numParameter, 50, iterations, function_ptr);
    ga->setMutationUniform();
    ga->setElite(2);
    //ga->setMutationProb(0.1);
    ga->population->setMaxParameter(0, 1000);
    ga->population->setMaxParameter(1, 1000);
    ga->setStopCriteria(stopCriteria);
    ga->search();
    delete(ga);
    cout<<"================================="<<endl;
    HillClimbing *hc = new HillClimbing(numParameter, iterations, function_ptr);
    hc->population->setNoise(0.1);
    hc->population->setMaxParameter(0, 1000);
    hc->population->setMaxParameter(1, 1000);
    hc->setStopCriteria(stopCriteria);
    hc->search();
    delete(hc);
    cout<<"================================="<<endl;

    SimulatedAnnealing *sa = new SimulatedAnnealing(numParameter, iterations, function_ptr);
    sa->population->setNoise(0.1);
    sa->setInitialTemperature(10.0);
    sa->population->setMaxParameter(0, 1000);
    sa->population->setMaxParameter(1, 1000);
    sa->setStopCriteria(stopCriteria);
    sa->search();
    delete(sa);
    cout<<"================================="<<endl;

}

int main() {
    for(int i=0;i<1;i++){
        run();
    }

    return 0;
}


