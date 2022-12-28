//
// Created by ricar on 28/12/2022.
//

#include "HillClimbing.h"
/**
 *
 * @param paramSize
 * @param iterNumber
 * @param eval_function
 */
HillClimbing::HillClimbing(int paramSize, int iterNumber, double(*eval_function)(vector<double>)):
        OptimizationMethod(paramSize, iterNumber, eval_function){
        this->setNoise(0.01);
        this->paramSet = new ParameterSet(0, this->getParameterSetSize(), this->getMinParameterSet(), this->getMaxParameterSet(), eval_function);
}
HillClimbing::~HillClimbing(){

}
/**
 *
 */
void HillClimbing::makeNoise(){

}
void HillClimbing::search(){
    for(int it=1;it<=this->iterationsNumber;it++){
        this->makeNoise();
    }

}