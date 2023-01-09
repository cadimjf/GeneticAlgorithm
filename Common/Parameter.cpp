
//
// Created by ricar on 26/12/2022.
//

#include "Parameter.h"
/**
 * Constructor
 * starts a Parameter with its max and min boudaries
 * @param min
 * @param max
 */
Parameter::Parameter(double min, double max){
    this->setMaxParameter(max);
    this->setMinParameter(min);
    this->setParameter(0.0);
}
/**
 *  set the max boundary for the Parameter
 * @param max
 */
void Parameter::setMaxParameter(double max) {
    this->parameterMax = max;
}
/**
 *  set the min boundary for the Parameter
 * @param min
 */
void Parameter::setMinParameter(double min){
    this->parameterMin = min;
}
/**
 *
 * @param a
 */
void Parameter::setParameter(double p){
    this->parameter = p;
}