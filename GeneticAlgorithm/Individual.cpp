//
// Created by ricar on 26/12/2022.
//

#include "Individual.h"
/**
 *
 * @param i
 * @param generationMax
 * @param mutationProb
 * @param mutationB
 * @param pS
 * @param cs
 * @param min
 * @param max
 * @param func_ptr_fit
 */
Individual::Individual(int i, double mutationProb, int cs, int mutType,
                       vector<double> min, vector<double> max, double(*func_ptr_fit)(vector<double>))
{
    this->mutType = mutType;
    this->function_ptr_fitness = func_ptr_fit;
    this->chromosomeSize = cs;
    this->chromosome = new ParameterSet(this->chromosomeSize, min, max);
    //initialize the aux chromossome with a copy from the chromossomes
    for (int i=0;i<this->chromosomeSize;i++){
        this->chromosomeAUX.push_back(this->chromosome->getParameter(i));
    }
    this->fitness = 0.0;
    this->mutationProb = mutationProb;

    this->id = i;
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
    return doubleRandom( this->chromosome->getMaxParameter(i),
                         this->chromosome->getMinParameter(i),
                         &this->individualRandomGenerator);
}

/**
 *
 * @param y
 * @return
 */
double Individual::delta(double y, int generation, int maxGeneration, double b) {
    double r = doubleRandom(0.0, 1.0, &this->individualRandomGenerator);
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
    int theta = intRandom(0, 1, &this->individualRandomGenerator);
    double aux = (theta == 0) ?
                 (this->chromosome->getMaxParameter(i) - gene) :
                 (gene - this->chromosome->getMinParameter(i));
    double d = delta(aux, generation, maxGeneration, b);
    double m = fabs(gene + d);
    return m;

}
/***
 *
 */
void Individual::mutate(int generation=0, int maxGeneration=0, double b=0.0) {

    for (int i = 0; i < this->chromosomeSize; i++) {
        //generate a random number
        double myDice = doubleRandom(0.0, 1.0, &this->individualRandomGenerator);
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

            this->setChromossomeAux(i , newGene);
        }
    }

}

/**
 *
 */
void Individual::iniChromossome()
{
    for (int i = 0; i < this->chromosomeSize; i++) {
        double x = uniformMutation(i);
        this->chromosome->setParameter(i, x);
        this->setChromossomeAux(i, x);
    }
}
/**
 *
 * @param i
 * @return
 */
double Individual::getGene(int i){
    return this->chromosome->getParameter(i);

}
/**
 * Copies alleles from chromosomeAUX to realchromossomes
 */
void Individual::updateChromossome(){
    for (int i=0;i<this->chromosomeSize;i++){
        this->chromosome->setParameter(i, this->chromosomeAUX[i]);
    }
}
/**
 *
 * @param i
 * @param val
 */
void Individual::setChromossomeAux(int i, double val){
    this->chromosomeAUX.at(i) = val;
 }
/**
 *
 * @param i
 * @return
 */
double Individual::getChromossomeAux(int i){
    return this->chromosomeAUX.at(i) ;
}
/**
 *
 * @return
 */
double Individual::getFitness(){
    return this->fitness;
}
/**
 *
 */
void Individual::computeFitness(){
    //computes the fitness (defined by user)
    this->fitness = this->function_ptr_fitness(this->chromosomeAUX);
    //After applying all genetic operation in the generation,
    //puts the new genes in the individual chromosome
    this->updateChromossome();

}

void Individual::printInfo(){
    cout<<"Fitness: "<<this->getFitness()<<endl;
    cout<<"ID: "<<this->getId()<<endl;
    cout<<"Chromossome: "<<endl;
    for (int i=0;i<this->chromosomeSize;i++){
        cout<<this->chromosome->getParameter(i)<<" ";
    }
    cout<<endl;

}