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
    void iniParameterSetBoundaries();
    void setMinParameter(int i, double val);
    void setMaxParameter(int i, double val);
    int getParameterSetSize();
    vector<double> getMinParameterSet(){return minParameterSet;};
    vector<double> getMaxParameterSet(){return maxParameterSet;};
    virtual void search()=0;
    void setStopCriteria(double s){stopCriteria=s;}
    double getStopCriteria(){return stopCriteria;}
 private:
    std::vector<double> maxParameterSet;
    std::vector<double> minParameterSet;
    int parameterSetSize;


protected:
    double stopCriteria;
    double(*evaluation_function)(vector<double>);
    std::default_random_engine randomGenerator;
    int iterationsNumber;
    int iterationCurrent;

};


#endif //GENETICALGORITHM_OPTIMAZATIONMETHOD_H
