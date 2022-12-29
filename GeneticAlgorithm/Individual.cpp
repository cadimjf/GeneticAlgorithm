//
// Created by ricar on 26/12/2022.
//

#include "Individual.h"
/***
 *
 * @param i
 * @param mutationProb
 * @param cs
 * @param mutType
 * @param min
 * @param max
 * @param func_ptr_fit
 */
Individual::Individual(int id, int chromosomeSize, double mutationProb,  int mutType,
                       double(*fit_function)(vector<double>)):ParameterSet(id, chromosomeSize, fit_function)
{
    this->mutType = mutType;
    this->mutationProb = mutationProb;

}

/**
 *
 */
Individual::~Individual() {
}

/**
 *
 * @param i
 * @return
 */
double Individual::uniformMutation(int i) {
    return this->generateRandomParameter(i);
}

/**
 *
 * @param y
 * @return
 */
double Individual::delta(double y, int generation, int maxGeneration, double b) {
    double r = this->getRandomDouble(0.0, 1.0);
    return y * (1.0 - powf(r, powf(1.0 - double(generation) / double(maxGeneration), b)));
}

/**
 *
 * @param gene
 * @param geneLowerBound
 * @param geneUpperBound
 */
double Individual::nonUniformMutation(int i, int generation, int maxGeneration, double b) {
    if(generation==0 ){
        throw MyException("To use non uniform mutation, you have to inform the generation! ", __FILE__, __LINE__);
    }
    if(maxGeneration==0){
        throw MyException("To use non uniform mutation, you have to inform the max generation!", __FILE__, __LINE__);
    }
    if(fabs(b)<1.0e-8){
        throw MyException("To use non uniform mutation, you have to inform b parameter! call setMutationB or setMutationUniform() to use uniform mutation", __FILE__, __LINE__);
    }

    double gene = this->getGene(i);
    int theta = intRandom(0, 1, &this->randomGenerator);
    double aux = (theta == 0) ?
                 (this->getMaxParameter(i) - gene) :
                 (gene - this->getMinParameter(i));
    double d = delta(aux, generation, maxGeneration, b);
    double m = fabs(gene + d);
    return m;

}
/***
 *
 */
void Individual::mutate(int generation=0, int maxGeneration=0, double b=0.0) {

    for (int i = 0; i < this->getParametersNum(); i++) {
        //generate a random number
        double myDice = this->getRandomDouble(0.0, 1.0);
        //check my random number with mutation probability
        if (myDice<this->mutationProb) {
            double newGene;
            if(mutType==MUTATION_NONUNIFORM){
                newGene = nonUniformMutation(i, generation, maxGeneration, b);
            }else if(mutType==MUTATION_UNIFORM){
                newGene = uniformMutation(i);
            }else{
                throw MyException("Invalid mutation type! ", __FILE__, __LINE__);
            }
            this->setParameterAux(i , newGene);
        }
    }

}


/**
 *
 * @param i
 * @return
 */
double Individual::getGene(int i){
    return this->getParameter(i);

}

/**
 *
 */
void Individual::computeFitness(){
    //computes the fitness (defined by user)
    this->evaluate();
    //After applying all genetic operation in the generation,
    //puts the new genes in the individual chromosome
    this->updateParameters();

}

void Individual::printInfo(){
    cout<<"Fitness: "<<this->getEvaluationValue()<<endl;
    cout<<"ID: "<<this->getId()<<endl;
    cout<<"Chromossome: "<<endl;
    this->print();

}
