#include <iostream>
#include <vector>
#include "OptimizationAlgorithms.h"
using namespace std;

double myFunction(double x, double y){
    return -x*x + x*y -y + 5.0;
}
double myFitness(vector<double> param){
    double res = myFunction(param.at(0), param.at(1));
    return fabs(res);
}

void run(){
    vector<double> myFirstGuess;
    myFirstGuess.push_back(10.0);
    myFirstGuess.push_back(10.0);
    double noise  = 0.3;

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
    //ga->population->popItems.at(0)->insertItem(myFirstGuess);
    ga->search();
    delete(ga);
    cout<<"================================="<<endl;
    
    HillClimbing *hc = new HillClimbing(numParameter, iterations, function_ptr);
    hc->population->setNoise(noise);
    hc->population->setMaxParameter(0, 1000);
    hc->population->setMaxParameter(1, 1000);
    hc->setStopCriteria(stopCriteria);
    //hc->population->popItems.at(0)->insertItem(myFirstGuess);
    hc->search();
    delete(hc);
    cout<<"================================="<<endl;

    SimulatedAnnealing *sa = new SimulatedAnnealing(numParameter, iterations, function_ptr);
    sa->population->setNoise(noise);
    sa->setInitialTemperature(10.0);
    sa->population->setMaxParameter(0, 1000);
    sa->population->setMaxParameter(1, 1000);
    sa->setStopCriteria(stopCriteria);
    //sa->population->popItems.at(0)->insertItem(myFirstGuess);
    sa->search();
    delete(sa);
    cout<<"================================="<<endl;


    AntColony *ac = new AntColony(numParameter, 5, 50, iterations, function_ptr);
    ac->population->setMaxParameter(0, 1000);
    ac->population->setMaxParameter(1, 1000);
    ac->setStopCriteria(stopCriteria);
    //ac->population->popItems.at(0)->insertItem(myFirstGuess);
    ac->search();
    delete(ac);
    cout<<"================================="<<endl;

}

int main() {
    for(int i=0;i<1;i++){
        run();
    }

    return 0;
}


