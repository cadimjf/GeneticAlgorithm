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
    this->population->initialize();
    this->temperature=0.0;
    this->energy=0.0;
}
/**
 *
 */
SimulatedAnnealing::~SimulatedAnnealing(){
    delete(this->population);

}
/**
 *
 * @param i
 * @return
 */
double SimulatedAnnealing::getMinNewParameter(int i){
    double parameterNoised = this->population->popItems.at(0)->getParameter(i); - this->getNoise();
    if (parameterNoised<this->population->popItems.at(0)->getMinParameter(i)){
        return this->population->popItems.at(0)->getMinParameter(i);
    }else{
        return parameterNoised;
    }
}
/**
 *
 * @param i
 * @return
 */
double SimulatedAnnealing::getMaxNewParameter(int i){
    double parameterNoised = this->population->popItems.at(0)->getParameter(i) + this->getNoise();
    if (parameterNoised > this->population->popItems.at(0)->getMaxParameter(i)){
        return this->population->popItems.at(0)->getMaxParameter(i);
    }else{
        return parameterNoised;
    }
}
/**
 *
 */
void SimulatedAnnealing::search(){

    double curEvaluation=std::numeric_limits<double>::lowest();
    double newEvaluation=0.0;
    int it=1;
    for(it=1;it<=this->iterationsNumber;it++){
        //disturb the parameters
        this->populamakeNoise();
        this->population->popItems.at(0)->evaluate();
        newEvaluation =this->population->popItems.at(0)->getEvaluationValue();
        if(eval>curEvaluation){
            //accept the new parameters
            this->population->popItems.at(0)->updateParameters();
            //updates the curEvaluation
            curEvaluation = eval;
        }
        if(curEvaluation<=this->getStopCriteria()){
            cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
            break;
        }
    }
    cout<<"Evaluation: "<<curEvaluation<<endl;
    cout<<"Iterations : "<<it<<endl;
    this->population->popItems.at(0)->print();

}
