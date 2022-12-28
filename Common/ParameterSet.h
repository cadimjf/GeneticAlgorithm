//
// Created by ricar on 26/12/2022.
//

#ifndef COMMON_PARAMETERSET_H
#define COMMON_PARAMETERSET_H

#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <vector>
#include "Parameter.h"
#include "MyUtil.h"

using namespace std;

class ParameterSet {
private:
    std::vector<Parameter*> parameters;
    int parametersNum;
public:
    ParameterSet(int, vector<double> min, vector<double> max);
    virtual ~ParameterSet();
    void setParameter(int i, double val);
    double getMaxParameter(int);
    double getMinParameter(int);
    double getParameter(int i);


};



#endif //COMMON_PARAMETERSET_H
