//
// Created by ricar on 26/12/2022.
//

#include "ParameterSet.h"
/**
 *
 * @param chromoSize
 * @param min
 * @param max
 */
ParameterSet::ParameterSet(int id, int numPar, double(*eval_func)(vector<double>) ){
    this->id = id;
    this->eval_function =eval_func;
    this->evalutionValue = 0.0;
    this->evalutionValueAux=0.0;
    this->parametersNum = numPar;
    //create parameters set
    for(int i =0; i<this->parametersNum; i++){
        Parameter *p = new Parameter(0.0, 100.0);
        this->parameters.push_back(p);
        //initialize the aux parameters set with a copy from the parameters
        this->parametersAUX.push_back(this->parameters.at(i)->getParameter());
    }
    //o seed é a hora do relógio + o id do indíviduo + 1. Se tirar o um, o seed do indivíduo 0 fica igual ao global
    unsigned seed = chrono::system_clock::now().time_since_epoch().count()+id+1;
    //starts my random generator with the seed
    default_random_engine gen(seed);
    this->randomGenerator = gen;
}

/**
 *
 * @return
 */
int ParameterSet::getId() {
    return this->id;
}

/**
 *
 */
ParameterSet::~ParameterSet(){
    this->parameters.clear();
    this->parametersAUX.clear();
}
/**
 *
 * @param i
 * @param val
 */
void ParameterSet::setParameter(int i, double val){
    this->parameters.at(i)->setParameter(val);
}
/**
 *
 * @param i
 * @return
 */
double ParameterSet::getMaxParameter(int i){
    return this->parameters.at(i)->getMaxParameter();
}
/**
 *
 * @param i
 * @return
 */
double ParameterSet::getMinParameter(int i){
    return this->parameters.at(i)->getMinParameter();
}
/**
 *
 * @param i
 */
double ParameterSet::getParameter(int i){
    return this->parameters.at(i)->getParameter();
}

/**
 *
 * @param i
 * @param val
 */
void ParameterSet::setParameterAux(int i, double val){
    this->parametersAUX.at(i) = val;
}
/**
 *
 * @param i
 * @return
 */
double ParameterSet::getParameterAux(int i){
    return this->parametersAUX.at(i) ;
}

/**
 * Copies alleles from chromosomeAUX to realchromossomes
 */
void ParameterSet::updateParameters(){
    //update the set of parameters
    for (int i=0;i<this->parametersNum;i++){
        this->setParameter(i,  this->getParameterAux(i) ) ;
    }
    //udates the fitness too
    this->evalutionValue = this->evalutionValueAux;
}
/**
 *
 * @param i
 * @return
 */
double ParameterSet::generateRandomParameter(int i){

    double x = this->getRandomDouble(   this->getMinParameter(i),
                                    this->getMaxParameter(i));
    return x;
}

double ParameterSet::getRandomDouble(double min, double max){
    return doubleRandom( min, max, &this->randomGenerator);
}

/**
 * Random start a single value of the set
*/
void ParameterSet::iniParameter(int i){
    double x = generateRandomParameter(i);
    this->setParameter(i, x);
    this->setParameterAux(i, x);

}
/**
 *
 */
void ParameterSet::iniParameterSet()
{
    for (int i = 0; i < this->getParametersNum(); i++) {
        this->iniParameter(i);
    }
}
/**
 * 
 * */
double  ParameterSet::evaluate(){
    this->evalutionValueAux =  this->eval_function(this->parametersAUX);
    return evalutionValueAux;
}
/**
*/
void ParameterSet::print(){
    cout<<"Parameter set: "<<endl;
    for (int i=0;i<this->getParametersNum();i++){
        cout<<this->getParameter(i)<<" ";
    }
    cout<<endl;
}


void ParameterSet::setMaxParameter(int i, double val){
    this->parameters.at(i)->setMaxParameter(val);
    this->iniParameter(i);
}

void ParameterSet::setMinParameter(int i, double val){
    this->parameters.at(i)->setMinParameter(val);
    this->iniParameter(i);
}

void ParameterSet::insertItem(vector<double> v){
    if(v.size() != this->parametersNum){
        throw MyException("Invalid number of parameters to insert!", __FILE__, __LINE__);
    }
    for(int i=0;i<this->parametersNum;i++){
        this->setParameter(i, v.at(i));
        this->setParameterAux(i, v.at(i));    
    }
    
}