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
    double (*function_ptr)(vector<double>) = &myFitness;
    //(*function_ptr)()
    GeneticAlgorithm *ga = new GeneticAlgorithm(2, 50, 1000, function_ptr);
    ga->setMutationUniform();
    ga->setElite(2);
    //ga->setMutationProb(0.1);
    ga->population->setMaxParameter(0, 1000);
    ga->population->setMaxParameter(1, 1000);
    ga->setStopCriteria(0.0003);
    ga->search();
    delete(ga);
    cout<<"================================="<<endl;
    HillClimbing *hc = new HillClimbing(2, 100000, function_ptr);
    hc->population->setNoise(0.1);
    hc->population->setMaxParameter(0, 1000);
    hc->population->setMaxParameter(1, 1000);
    hc->setStopCriteria(0.0003);
    hc->search();
    delete(hc);
    cout<<"================================="<<endl;

    SimulatedAnnealing *sa = new SimulatedAnnealing(2, 100000, function_ptr);
    sa->population->setNoise(0.1);
    sa->setInitialTemperature(100000.0);
    sa->population->setMaxParameter(0, 1000);
    sa->population->setMaxParameter(1, 1000);
    sa->setStopCriteria(0.0003);
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


