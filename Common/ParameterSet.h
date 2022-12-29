//
// Created by ricar on 26/12/2022.
//

#ifndef COMMON_PARAMETERSET_H
#define COMMON_PARAMETERSET_H

#include <random> /* srand, rand */
#include <time.h>       /* time */
#include <chrono>

#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <vector>
#include "Parameter.h"
#include "MyUtil.h"
#include "Random.h"
using namespace std;

class ParameterSet {
private:
    std::vector<Parameter*> parameters;
    std::vector<double> parametersAUX;
    double(*eval_function)(vector<double>);
    int parametersNum;
    int     id;
    double evalutionValue;
    double evalutionValueAux;

public:

    int   getId();
    ParameterSet(int, int, double(*eval_func)(vector<double>));
    ~ParameterSet();
    int getParametersNum(){return parametersNum;};
    void setParameter(int i, double val);
    double getMaxParameter(int);
    double getMinParameter(int);
    double getParameter(int i);
    void updateParameters();
    void setParameterAux(int i, double val);
    double getParameterAux(int);
    void    iniParameters();
    void changeBounds(int iChron, double min, double max);
    double generateRandomParameter(int);
    double evaluate();
    double getRandomDouble(double min, double max);
    void print();
    void setMaxParameter(int i, double val);
    void setMinParameter(int i, double val);
    double getEvaluationValue(){return evalutionValue;};
protected:
    default_random_engine randomGenerator;

};



#endif //COMMON_PARAMETERSET_H
