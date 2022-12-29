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
    this->population->initialize();
    double curEvaluation=std::numeric_limits<double>::lowest();
    double eval=0.0;
    iterationCurrent=1;
    do{
        //disturb the parameters
        this->population->makeNoise();
        eval = this->population->popItems.at(0)->evaluate();
        if(eval>curEvaluation){
            //accept the new parameters
            this->population->popItems.at(0)->updateParameters();
            //updates the curEvaluation
            curEvaluation = eval;
        }
        iterationCurrent++;
        if(curEvaluation<=this->getStopCriteria()){
            cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
            break;
        }
    }while(iterationCurrent<iterationsNumber);
    cout<<"Evaluation: "<<curEvaluation<<endl;
    cout<<"Iterations : "<<iterationCurrent<<endl;
    this->population->popItems.at(0)->print();

}
