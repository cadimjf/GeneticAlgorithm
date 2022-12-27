//
// Created by ricar on 26/12/2022.
//

#include "Chromosome.h"
/**
 *
 * @param chromoSize
 * @param min
 * @param max
 */
Chromosome::Chromosome(int chromoSize, vector<double> min, vector<double> max){
    this->chromosomeSize = chromoSize;
    for(int i =0; i<this->chromosomeSize; i++){
        Gene *g = new Gene(min[i], max[i]);
        this->genes.push_back(g);
    }

}
/**
 *
 */
Chromosome::~Chromosome(){

}
/**
 *
 * @param i
 * @param val
 */
void Chromosome::setAllele(int i, double val){
    if(i<0 || i>=this->chromosomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    this->genes[i]->setAllele(val);
}
/**
 *
 * @param i
 * @return
 */
double Chromosome::getMaxAllele(int i){
    if(i<0 || i>=this->chromosomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    return this->genes[i]->getAlleleMax();
}
/**
 *
 * @param i
 * @return
 */
double Chromosome::getMinAllele(int i){
    if(i<0 || i>=this->chromosomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    return this->genes[i]->getAlleleMin();
}
/**
 *
 * @param i
 */
double Chromosome::getAllele(int i){
    if(i<0 || i>=this->chromosomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    return this->genes[i]->getAllele();
}

