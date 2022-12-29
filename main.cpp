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
void run(){
    double (*function_ptr)(vector<double>) = &myFitness;
    //(*function_ptr)()
    GeneticAlgorithm *ga = new GeneticAlgorithm(2, 50, 1000, function_ptr);
    ga->setMutationUniform();
    ga->setElite(2);
    //ga->setMutationProb(0.1);
    //ga->population->setMaxParameter(0, 1000);
    //ga->setMinParameter(1, 100);
    //ga->population->setMaxParameter(1, 10);
    ga->setStopCriteria(0.0003);
    ga->search();
    delete(ga);
    //cout<<"================================="<<endl;
    /*
    HillClimbing *hc = new HillClimbing(2, 10000, function_ptr);
    hc->setNoise(0.001);
    hc->population->setMaxParameter(0, 1000);
    hc->population->setMaxParameter(1, 1000);
    hc->setStopCriteria(0.0003);
    hc->search();
    delete(hc);
    cout<<"================================="<<endl;*/

}

int main() {
    for(int i=0;i<1;i++){
        run();
    }

    return 0;
}


