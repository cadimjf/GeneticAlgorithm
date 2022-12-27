//
// Created by ricar on 26/12/2022.
//

#include "Individual.h"
/*
 * File:   Individual.cpp
 * Author: Ricardo
 *
 * Created on 1 de Agosto de 2014, 15:17
 */

Individual::Individual(int i, int generationMax, double mutationProb,
                       double mutationB, int pS, int cs,
                       vector<double> min, vector<double> max)
{
    this->chromosomeSize = cs;
    this->chromosome = new Chromosome(this->chromosomeSize, min, max);
    //initialize the aux chromossome with a copy from the chromossomes
    for (int i=0;i<this->chromosomeSize;i++){
        this->chromosomeAUX.push_back(this->chromosome->getAllele(i));
    }
    this->populationSize = pS;
    this->b = mutationB;
    this->maxGeneration = generationMax;

    this->mutationProb = mutationProb;

    this->id = id;
    //o seed é a hora do relógio + o id do indíviduo + 1. Se tirar o um, o seed do indivíduo 0 fica igual ao global
    unsigned seed = chrono::system_clock::now().time_since_epoch().count()+id+1;
    //starts my random generator with the seed
    default_random_engine gen(seed);
    this->individualRandomGenerator = gen;


}

/**
 *
 */
Individual::~Individual() {
    if(this->chromosome!=NULL) delete(this->chromosome);
}
/*
/**
 *
 * @return
 */
int Individual::getId() {
    return this->id;
}


/**
 *
 * @param i
 * @return
 */
double Individual::uniformMutation(int i) {
    return doubleRandom( this->chromosome->getMaxAllele(i),
                         this->chromosome->getMinAllele(i),
                         &this->individualRandomGenerator);
}

/**
 *
 * @param y
 * @return
 */
double Individual::delta(double y) {
    double r = doubleRandom(0.0, 1.0, &this->individualRandomGenerator);
    return y * (1.0 - powf(r, powf(1.0 - double(this->generation) / double(this->maxGeneration), this->b)));
}

/**
 *
 * @param gene
 * @param geneLowerBound
 * @param geneUpperBound
 */
double Individual::nonUniformMutation(int i, double gene) {
/*//    double gene = this->getGeneByIndex(i);
    int theta = intRandom(0, 1, &this->individualRandomGenerator);
    double aux = (theta == 0) ?
                 (this->cromos->getUpperBound(i) - gene) :
                 (gene - this->cromos->getLowerBound(i));
    double d = delta(aux);
    return fabs(gene + d);*/

}

/**
 *
 */
void Individual::mutate() {
    /*double *myCromo = (double*)malloc(sizeof(double)*this->getChromoLength());
    this->getChromosome(myCromo);

    for (int i = 0; i < this->getChromoLength(); i++) {
        //generate a random number
        double myDice = doubleRandom(0.0, 1.0, &this->individualRandomGenerator);
        //check my random number with mutation probability
        if (myDice<this->mutationProb) {
            myCromo[i] = nonUniformMutation(i, myCromo[i]);
        }
    }
    this->setChromosome(myCromo);
    free(myCromo);*/
}

/**
 *
 */
void Individual::iniChromossome()
{
    for (int i = 0; i < this->chromosomeSize; i++) {
        double x = uniformMutation(i);
        this->chromosome->setAllele(i, x);

    }
}
/**
 *
 * @param i
 * @return
 */
double Individual::getGene(int i){
    return this->chromosome->getAllele(i);

}
/**
 * Copies alleles from chromosomeAUX to realchromossomes
 */
void Individual::updateChromossome(){
    for (int i=0;i<this->chromosomeSize;i++){
        this->chromosome->setAllele(i, this->chromosomeAUX[i]);
    }
}

void Individual::setChromossomeAux(int i, double val){
    if(i<0 || i>=this->chromosomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    this->chromosomeAUX[i] = val;
}