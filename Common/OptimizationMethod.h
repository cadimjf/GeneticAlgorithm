//
// Created by ricar on 28/12/2022.
//

#ifndef GENETICALGORITHM_OPTIMIZATIONMETHOD_H
#define GENETICALGORITHM_OPTIMIZATIONMETHOD_H

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
class OptimizationMethod {
public:
    OptimizationMethod(int paramSetSize, double(*eval_function)(vector<double>));
    ~OptimizationMethod();
    void iniParameterSetBoundaries();
    void setMinParameter(int i, double val);
    void setMaxParameter(int i, double val);
    int getParameterSetSize();
    vector<double> getMinParameterSet(){return minParameterSet;};
    vector<double> getMaxParameterSet(){return maxParameterSet;};

 private:
    std::vector<double> maxParameterSet;
    std::vector<double> minParameterSet;
    int parameterSetSize;

protected:
    double(*evaluation_function)(vector<double>);

};


#endif //GENETICALGORITHM_OPTIMAZATIONMETHOD_H
