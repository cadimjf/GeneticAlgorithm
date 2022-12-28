//
// Created by ricar on 28/12/2022.
//

#include "HillClimbing.h"

HillClimbing::HillClimbing(int paramSize, int iterNumber, double(*eval_function)(vector<double>) ):
        OptimizationMethod(paramSize, iterNumber, eval_function){
        this->setNoise(0.01);
}
HillClimbing::~HillClimbing(){

}
void HillClimbing::search(){
    //for(int it=0;)

}