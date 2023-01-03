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
    this->temperature=0.0;
    this->deltaE=0.0;
}
/**
 *
 */
SimulatedAnnealing::~SimulatedAnnealing(){
    delete(this->population);

}

double SimulatedAnnealing::getProbability(double deltaE, double t){

    return exp(deltaE/temperature);
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
    double bestEvaluation=newEvaluation;
    
    int it=1;
    for(it=1;it<=this->iterationsNumber;it++){
        //disturb the parameters
        this->populamakeNoise();
        this->population->popItems.at(0)->evaluate();
        newEnergy =this->population->popItems.at(0)->getEvaluationValue();
        deltaE = newEvaluation - currentEnergy;
        // looking for the mininum
        if(newEvaluation < currentEvaluation){
            //accept the new parameters
            this->population->popItems.at(0)->updateParameters();
            //updates the curEvaluation
            currentEvaluation = newEvaluation;
        }else{
            //the new evaluation is worse than the current
            //accept under probability of e^(deltaE/T)

        }
        if(currentEvaluation<=this->getStopCriteria()){
            cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
            break;
        }
    }
    cout<<"Evaluation: "<<currentEvaluation<<endl;
    cout<<"Iterations : "<<it<<endl;
    this->population->popItems.at(0)->print();

}
