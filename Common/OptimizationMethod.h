//
// Created by ricar on 28/12/2022.
//

#ifndef GENETICALGORITHM_OPTIMIZATIONMETHOD_H
#define GENETICALGORITHM_OPTIMIZATIONMETHOD_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random> /* srand, rand */
#include <time.h>       /* time */
#include <chrono>

using namespace std;

class OptimizationMethod {
public:
    OptimizationMethod(int paramSetSize, int iterationsNumber, double(*eval_function)(vector<double>));
    ~OptimizationMethod();
    int getParameterSetSize();
    virtual void search()=0;
    void setStopCriteria(double s){stopCriteria=s;}
    double getStopCriteria(){return stopCriteria;}
 private:
    int parameterSetSize;

protected:
    double stopCriteria;
    double(*evaluation_function)(vector<double>);
    std::default_random_engine randomGenerator;
    int iterationsNumber;
    int iterationCurrent;

};


#endif //GENETICALGORITHM_OPTIMAZATIONMETHOD_H
