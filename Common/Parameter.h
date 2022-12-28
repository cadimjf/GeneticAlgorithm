//
// Created by ricar on 26/12/2022.
//

#ifndef COMMON_PARAMETER_H
#define COMMON_PARAMETER_H
#include <iostream>
#include <vector>

class Parameter {
private:
    int id;
    double parameter;
    double parameterMax;
    double parameterMin;
public:
    Parameter(double min, double max);
    void setParameter(double);
    void setMaxParameter(double);
    void setMinParameter(double);
    int getId(){return id;}
    double getParameter(){return parameter;}
    double getMaxParameter(){return parameterMax;}
    double getMinParameter(){return parameterMin;}
};


#endif //COMMON_PARAMETER_H
