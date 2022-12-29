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
        this->setNoise(0.01);
        this->population = new Population<ParameterSet*>(1, paramSize);
        this->population->insertPopulationItem(new ParameterSet(0, paramSize, eval_function));
        this->population->initialize();
}
/**
 *
 */
HillClimbing::~HillClimbing(){
    delete(this->population);

}
/**
 *
 * @param i
 * @return
 */
double HillClimbing::getMinNewParameter(int i){
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
double HillClimbing::getMaxNewParameter(int i){
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
void HillClimbing::makeNoise(){
    double newParam = 0.0;
    for(int i=0; i<this->population->popItems.at(0)->getParametersNum();i++){
        //the interval is from -noise : +noisa
        newParam = this->population->popItems.at(0)->getRandomDouble(getMinNewParameter(i), getMaxNewParameter(i));
        this->population->popItems.at(0)->setParameterAux(i, newParam);
    }
}
/**
 *
 */
void HillClimbing::search(){

    double curEvaluation=std::numeric_limits<double>::lowest();
    double eval=0.0;
    int it=1;
    for(it=1;it<=this->iterationsNumber;it++){
        //disturb the parameters
        this->makeNoise();
        this->population->popItems.at(0)->evaluate();
        eval =this->population->popItems.at(0)->getEvaluationValue();
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

/**
 *
 * @param i
 * @param val
 */
void HillClimbing::setMaxParameter(int i, double val){
    this->population->popItems.at(0)->setMaxParameter(i, val);
}
/**
 *
 * @param i
 * @param val
 */
void HillClimbing::setMinParameter(int i, double val){
    this->population->popItems.at(0)->setMinParameter(i, val);
}