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
        this->paramSet = new ParameterSet(0, this->getParameterSetSize(), eval_function);
}
HillClimbing::~HillClimbing(){
    delete(this->paramSet);

}
/**
 *
 */
void HillClimbing::makeNoise(){
    double maxParam=0.0, minParam=0.0, newParam = 0.0, oldParam=0.0;
    double minBound, maxBound;
    for(int i=0; i<this->paramSet->getParametersNum();i++){
        oldParam = this->paramSet->getParameter(i);
        minBound = this->paramSet->getMinParameter(i);
        maxBound = this->paramSet->getMaxParameter(i);
        //the interval is from -noise : +noisa
        minParam = oldParam - this->getNoise();
        minParam = (minParam<minBound)?minBound:minParam;
        //
        maxParam = oldParam + this->getNoise();
        maxParam = (maxParam>maxBound)?maxBound:maxParam;
        newParam = this->paramSet->getRandomDouble(minParam, maxParam);
        this->paramSet->setParameterAux(i, newParam);
    }

}
void HillClimbing::search(){
    this->paramSet->iniParameters();
    double curEvaluation=std::numeric_limits<double>::lowest();
    double eval=0.0;
    int it=1;
    for(it=1;it<=this->iterationsNumber;it++){
        //disturb the parameters
        this->makeNoise();
        eval = this->paramSet->evaluate();
        if(eval>curEvaluation){
            //accept the new parameters
            this->paramSet->updateParameters();
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
    this->paramSet->print();

}

/**
 *
 * @param i
 * @param val
 */
void HillClimbing::setMaxParameter(int i, double val){
    this->paramSet->setMaxParameter(i, val);
}
/**
 *
 * @param i
 * @param val
 */
void HillClimbing::setMinParameter(int i, double val){
    this->paramSet->setMinParameter(i, val);
}