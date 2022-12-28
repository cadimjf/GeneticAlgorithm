//
// Created by ricar on 28/12/2022.
//

#include "OptimizationMethod.h"
/***
 * Receives the number of parameters and the user-defined evaluationfunction
 * @param paramSetSize
 * @param eval_function
 */
using namespace std;
OptimizationMethod::OptimizationMethod(int paramSetSize, int iterationsNumber, double(*eval_function)(vector<double>)) {
    this->parameterSetSize      = paramSetSize;
    this->evaluation_function   = eval_function;
    this->iterationsNumber = iterationsNumber;
    this->iniParameterSetBoundaries();
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    //starts my random generator with the seed
    std::default_random_engine gen(seed);
    this->randomGenerator = gen;
}
/**
 *
 */
OptimizationMethod::~OptimizationMethod() {
    this->maxParameterSet.clear();
    this->minParameterSet.clear();
}
/**
 *
* set a max allele value for a specific gene (i)
* @param i
* @param val
*/
void OptimizationMethod::setMaxParameter(int i, double val){
    this->maxParameterSet.at(i) = val;
}
/**
 * set a min allele value for a specific gene (i)
 * @param i
 * @param val
 */
void OptimizationMethod::setMinParameter(int i, double val){
    this->minParameterSet.at(i)= val;
}
/**
 * sets a default boundary to each allele
 */
void OptimizationMethod::iniParameterSetBoundaries(){
    for(int i=0; i<this->parameterSetSize;i++){
        this->minParameterSet.push_back(0.0);
        this->maxParameterSet.push_back(1000.0);
    }
}
int OptimizationMethod::getParameterSetSize(){
    return this->parameterSetSize;
}