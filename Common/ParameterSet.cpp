//
// Created by ricar on 26/12/2022.
//

#include "ParameterSet.h"
/**
 *
 * @param chromoSize
 * @param min
 * @param max
 */
ParameterSet::ParameterSet(int numPar, vector<double> min, vector<double> max){
    this->parametersNum = numPar;
    for(int i =0; i<this->parametersNum; i++){
        Parameter *p = new Parameter(min[i], max[i]);
        this->parameters.push_back(p);
    }
}
/**
 *
 */
ParameterSet::~ParameterSet(){
    this->parameters.clear();
}
/**
 *
 * @param i
 * @param val
 */
void ParameterSet::setParameter(int i, double val){
    this->parameters.at(i)->setParameter(val);
}
/**
 *
 * @param i
 * @return
 */
double ParameterSet::getMaxParameter(int i){
    return this->parameters.at(i)->getMaxParameter();
}
/**
 *
 * @param i
 * @return
 */
double ParameterSet::getMinParameter(int i){
    return this->parameters.at(i)->getMinParameter();
}
/**
 *
 * @param i
 */
double ParameterSet::getParameter(int i){
    return this->parameters.at(i)->getParameter();
}

