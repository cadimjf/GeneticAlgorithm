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
Chromosome::Chromosome(int chromoSize, double *min, double* max){
    this->chromosomeSize = chromoSize;
    this->genes    = myAllocation<Gene*>(this->chromosomeSize);
    for(int i =0; i<this->chromosomeSize; i++){
        this->genes[i]->setAlleleMax(max[i]);
        this->genes[i]->setAlleleMin(min[i]);
    }

}
/**
 *
 */
Chromosome::~Chromosome(){
    if (this->genes   != NULL) free(this->genes);

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
    this->genes[i]->getAlleleMax();
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
    this->genes[i]->getAlleleMin();
}

