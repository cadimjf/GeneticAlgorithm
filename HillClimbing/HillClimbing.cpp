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
        OptimizationMethod(iterNumber, eval_function){
        this->population = new Population<ParameterSet*>(1, paramSize);
        this->population->setNoise(0.01);
        this->population->insertPopulationItem(new ParameterSet(0, paramSize, eval_function));

}
/**
 *
 */
HillClimbing::~HillClimbing(){
    delete(this->population);

}

/**
 *
 */
void HillClimbing::search(){
    //random start new solution
    this->population->initialize();
    //compute the evaluation
    double newEvaluation = this->population->popItems.at(0)->evaluate();
    //accept the new parameters
    this->population->popItems.at(0)->updateParameters();
    double bestEvaluation=newEvaluation;

    iterationCurrent=1;
    do{
        //disturb the parameters
        this->population->makeNoise();
        newEvaluation = this->population->popItems.at(0)->evaluate();
        // looking for the mininum - accepts the new solution if its evaluation is lower than the current
        if(newEvaluation < bestEvaluation){
            //accept the new parameters
            this->population->popItems.at(0)->updateParameters();
            //updates the curEvaluation
            bestEvaluation = newEvaluation;
        }
        iterationCurrent++;
        if(bestEvaluation<=this->getStopCriteria()){
            cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
            break;
        }
    }while(iterationCurrent<iterationsNumber);
    cout<<"Evaluation: "<<bestEvaluation<<endl;
    cout<<"Iterations : "<<iterationCurrent<<endl;
    this->population->popItems.at(0)->print();

}
