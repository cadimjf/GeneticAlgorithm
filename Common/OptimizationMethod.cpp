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
/**
 *
 * @param iterationsNumber
 * @param eval_function
 */
OptimizationMethod::OptimizationMethod( int iterationsNumber, double(*eval_function)(vector<double>)) {
    this->evaluation_function   = eval_function;
    this->iterationsNumber = iterationsNumber;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    //starts my random generator with the seed
    std::default_random_engine gen(seed);
    this->randomGenerator = gen;
}
/**
 *
 */
OptimizationMethod::~OptimizationMethod() {

}



