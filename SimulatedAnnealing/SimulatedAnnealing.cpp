//
// Created by ricar on 28/12/2022.
//

#include "SimulatedAnnealing.h"
/**
 *
 * @param paramSize
 * @param iterNumber
 * @param eval_function
 */
SimulatedAnnealing::SimulatedAnnealing(int paramSize, int iterNumber, double(*eval_function)(vector<double>)):
        OptimizationMethod(iterNumber, eval_function){

    this->population = new Population<ParameterSet*>(1, paramSize);
    this->population->insertPopulationItem(new ParameterSet(0, paramSize, eval_function));
    this->deltaE=0.0;
    this->temperatureInitial = 100.0;
}
/**
 *
 */
SimulatedAnnealing::~SimulatedAnnealing(){
    delete(this->population);

}
double SimulatedAnnealing::temperature(){
    return temperatureInitial / (double(this->iterationCurrent) + 1.0);
}
double SimulatedAnnealing::acceptProbability(){

    return exp(deltaE/this->temperature());
}
void SimulatedAnnealing::setInitialTemperature(double t0){
    this->temperatureInitial = t0;
}
/**
 *
 */
void SimulatedAnnealing::search(){

    //random start new solution
    this->population->initialize();
    //compute the evaluation
    double newEvaluation = this->population->popItems.at(0)->evaluate();
    //accept the new parameters
    this->population->popItems.at(0)->updateParameters();
    double currentEvaluation=newEvaluation;
    //search
    for(iterationCurrent=1;iterationCurrent<=this->iterationsNumber;iterationCurrent++){
        //disturb the parameters
        this->population->makeNoise();
        newEvaluation = this->population->popItems.at(0)->evaluate();
        //inverts the sign - it is a minimizations problem
        this->deltaE = -(newEvaluation - currentEvaluation);
        // looking for the mininum
        if(newEvaluation < currentEvaluation){
            //accept the new parameters
            this->population->popItems.at(0)->updateParameters();
            //updates the curEvaluation
            currentEvaluation = newEvaluation;
        }else{
            //the new evaluation is worse than the current
            //accept under probability of e^(deltaE/T)
            if(doubleRandom(0.0, 1.0, &this->randomGenerator) < this->acceptProbability()){
                //accept and worse solution
                 this->population->popItems.at(0)->updateParameters();
                //updates the curEvaluation
                currentEvaluation = newEvaluation;
            }

        }
        if(currentEvaluation<=this->getStopCriteria()){
            cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
            break;
        }
    }
    cout<<"Evaluation: "<<currentEvaluation<<endl;
    cout<<"Iterations : "<<iterationCurrent<<endl;
    cout<<"Temperature: "<<this->temperature()<<" - "<<this->acceptProbability()<<endl;
    this->population->popItems.at(0)->print();

}
