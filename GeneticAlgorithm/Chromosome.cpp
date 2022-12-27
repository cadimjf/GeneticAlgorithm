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
    this->genes.clear();
}
/**
 *
 * @param i
 * @param val
 */
void Chromosome::setAllele(int i, double val){
    this->genes.at(i)->setAllele(val);
}
/**
 *
 * @param i
 * @return
 */
double Chromosome::getMaxAllele(int i){
    return this->genes.at(i)->getAlleleMax();
}
/**
 *
 * @param i
 * @return
 */
double Chromosome::getMinAllele(int i){
    return this->genes.at(i)->getAlleleMin();
}
/**
 *
 * @param i
 */
double Chromosome::getAllele(int i){
    return this->genes.at(i)->getAllele();
}

