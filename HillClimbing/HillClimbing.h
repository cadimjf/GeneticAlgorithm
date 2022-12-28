//
// Created by ricar on 28/12/2022.
//

#ifndef GENETICALGORITHM_HILLCLIMBING_H
#define GENETICALGORITHM_HILLCLIMBING_H
#include "../Common/OptimizationMethod.h"
#include "../Common/ParameterSet.h"
class HillClimbing : public OptimizationMethod {
public:
    HillClimbing(int paramSize, int iterNumber, double(*eval_function)(vector<double>));
    ~HillClimbing();
    void search();
    void setNoise(double n){noise=n;};
    double getNoise(){return noise;};
private:
    double noise;
    ParameterSet *paramSet;
    void makeNoise();
};


#endif //GENETICALGORITHM_HILLCLIMBING_H
