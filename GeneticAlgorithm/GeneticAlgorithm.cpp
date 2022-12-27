//
// Created by ricar on 26/12/2022.
//

#include "GeneticAlgorithm.h"
using namespace std;
/**
 * Sets the elite size - the number of individuals kept to the next generation
 * @param e
 */
void GeneticAlgorithm::setElite(int e){
    this->elite = e;
}

/**
 * Sets the probability of crossover
 * @param cop
 */
void GeneticAlgorithm::setCrossOverProb(double cop){
    this->crossOverProb = cop;
}
/**
 * Sets the number of threads to openMP parallel directives
 * @param tn
 */
void GeneticAlgorithm::setThreadsNumber(int tn){
    this->numThreads = tn;
}
/**
 * set the alpha parameter to the BLX-alpha crossver
 * @param a
 */
void GeneticAlgorithm::setAlpha(double a){
    this->alpha = a;
}
/**
 * The b parameter of non-uniform mutation,
 * the parameter of delta calculation
 * @param mb
 */
void GeneticAlgorithm::setMutationB(double mb){
    this->mutationB = mb;
}
/**
 * The mutation probability
 * @param mp
 */
void GeneticAlgorithm::setMutationProb(double mp){
    this->mutationProb = mp;
}

/**
 * The genetic algorithm constructor
 * @param nPopulation
 * @param gm
 */
GeneticAlgorithm::GeneticAlgorithm(int chromoSize, int nPopulation=100, int gm=100)
{
    try {
        this->populationSize = nPopulation;
        this->avgFitness = 0.0;
        this->sumFit = 0.0;
        this->agSeed = time(NULL);
        this->iBest = 0;
        this->iWorst = this->populationSize - 1;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();

        //starts my random generator with the seed
        default_random_engine gen(seed);
        this->agRandomGenerator = gen;
        this->generationMax = gm;
        this->chromossomeSize = chromoSize;
        this->setElite(4);
        this->setCrossOverProb(0.95);
        this->setThreadsNumber(1);
        this->setAlpha(0.3);
        this->setMutationProb(0.05);
        this->setMutationB(3.0);
        this->iniAlleleBoundaries();
        cout<<"TEST"<<endl;

    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
    }
}
GeneticAlgorithm::~GeneticAlgorithm(){

}
/**
 * set a max allele value for a specific gene (i)
 * @param i
 * @param val
 */
void GeneticAlgorithm::setMaxAllele(int i, double val){
    if(i<0 || i>=this->chromossomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    this->maxAllele[i]= val;
}
/**
 * set a min allele value for a specific gene (i)
 * @param i
 * @param val
 */
void GeneticAlgorithm::setMinAllele(int i, double val){
    if(i<0 || i>=this->chromossomeSize) {
        throw MyException("index out of boundaries", __FILE__, __LINE__);
    }
    this->minAllele[i]= val;
}
/**
 * sets a default boundary to each allele
 */
void GeneticAlgorithm::iniAlleleBoundaries(){
    for(int i=0; i<this->chromossomeSize;i++){
        this->minAllele.push_back(0.0);
        this->maxAllele.push_back(1000.0);
    }
}
void GeneticAlgorithm::evolution(){
    try{
        cout<<"1"<<endl;
        this->iniPopulation();
        cout<<"2"<<endl;
    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
    }
}
void GeneticAlgorithm::iniPopulation(){
    cout<<"Pop size "<<this->populationSize<<endl;
    cout<<"Chromo size "<<this->chromossomeSize<<endl;
    cout<<"coisei pop"<<endl;
    for(int i=0; i<this->populationSize; i++)
    {
        this->population.push_back(new Individual(i,
                                             this->generationMax,
                                             this->mutationProb, this->mutationB,
                                             this->populationSize, this->chromossomeSize,
                                             this->minAllele, this->maxAllele));
        this->population[i]->iniChromossome();
    }

    for(int i=0; i<this->populationSize; i++){
        cout<<i<<endl;
        for(int j=0;j<this->chromossomeSize;j++){
            cout<<"\t"<<this->population[i]->getGene(j)<<endl;
        }

    }
}
