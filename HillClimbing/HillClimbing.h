//
// Created by ricar on 28/12/2022.
//

#ifndef GENETICALGORITHM_HILLCLIMBING_H
#define GENETICALGORITHM_HILLCLIMBING_H
#include "../Common/OptimizationMethod.h"
#include "../Common/ParameterSet.h"
#include "../Common/Population.h"
class HillClimbing : public OptimizationMethod {
public:
    HillClimbing(int paramSize, int iterNumber, double(*eval_function)(vector<double>));
    ~HillClimbing();
    void search();
    void setNoise(double n){noise=n;};
    double getNoise(){return noise;};
    void setMaxParameter(int i, double val);
    void setMinParameter(int i, double val);
    Population<ParameterSet*> *population;
private:
    double noise;

    void makeNoise();
    double getMaxNewParameter(int i);
    double getMinNewParameter(int i);
};


#endif //GENETICALGORITHM_HILLCLIMBING_H
