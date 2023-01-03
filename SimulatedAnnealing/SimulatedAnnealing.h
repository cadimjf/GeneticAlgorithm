//
// Created by ricar on 29/12/2022.
//

#ifndef GENETICALGORITHM_SIMULATEDANNEALING_H
#define GENETICALGORITHM_SIMULATEDANNEALING_H
#include "../Common/OptimizationMethod.h"
#include "../Common/Population.h"
#include "../Common/ParameterSet.h"
#include <math.h> 
using namespace std;

class SimulatedAnnealing: public OptimizationMethod {
public:
    SimulatedAnnealing(int paramSize, int iterNumber, double(*eval_function)(vector<double>));
    ~SimulatedAnnealing();
    void search();
    Population<ParameterSet*> *population;
    void setInitialTemperature(double);
private:
    double deltaE;
    double acceptProbability();
    double temperature();
    double temperatureInitial;

};

#endif //GENETICALGORITHM_SIMULATEDANNEALING_H
