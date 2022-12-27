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
        this->generationCurrent=0;
        //starts my random generator with the seed
        default_random_engine gen(seed);
        this->agRandomGenerator = gen;
        this->generationMax = gm;
        this->chromossomeSize = chromoSize;
        this->setElite(4);
        this->setCrossOverProb(0.95);
        this->setAlpha(0.3);
        this->setMutationProb(0.05);
        this->setMutationB(3.0);
        this->iniAlleleBoundaries();
        //used for rank selection - gives the sum of the position of all indivdual
        // 0 + 1 + 2 + ... + populationSize-1
        this->sumRank = (this->populationSize+1)*this->populationSize/2;

    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
    }
}
GeneticAlgorithm::~GeneticAlgorithm(){
    this->population.clear();
    this->maxAllele.clear();
    this->maxAllele.clear();
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


/**
 * Select one individual for reproductions
 *  Rank selection
  * @param forbidenGuy avoids selecting the same individual to form parents
  * -1 indicates anyone can be choosen
 * @return
 */
int GeneticAlgorithm::rankSelection(int forbidenGuy){
    //numero da sorte, para escolher o individuo atraves de roleta
    double myLuckNumber = doubleRandom(0.0, this->sumRank, &this->agRandomGenerator);
    double sumRank=0.0;
    int selectedParent=-1;
    for(int i=0; i<this->populationSize; i++){
        //the greatest value is given to the best fitness in the population
        //and the least is given to the tha last individual - worst fitness
        sumRank += (this->populationSize-i);
        if(sumRank>=myLuckNumber  && forbidenGuy!=i){//we found our guy
            selectedParent= i;
            break;
        }
    }
    if(selectedParent==-1)
        //If we got here, no one was select. Exception!
        throw MyException("No one was selected.", __FILE__, __LINE__);
    else
        return selectedParent;
}
/**
 * perform the blx-alpha croosover
 * @param gene1
 * @param gene2
 * @return
 */
double GeneticAlgorithm::crossOverBLXAlpha(double gene1, double gene2)
{
    double cMin, cMax, iMaxMin;
    if(gene1>gene2){
        cMax=gene1;
        cMin=gene2;
    }else{
        cMax=gene2;
        cMin=gene1;
    }
    iMaxMin = cMax-cMin;
    return doubleRandom(cMin-iMaxMin*this->alpha, cMax+iMaxMin*this->alpha, &this->agRandomGenerator);

}

/**
 *
 * @param p1
 * @param p2
 * @param iInd
 */
void GeneticAlgorithm::crossOver(int p1, int p2, int iInd)
{
    double myLuckyNumber = doubleRandom(0.0, 1.0, &this->agRandomGenerator);
///if the parents are the same or the crossover is not done
    if(p1==p2 || myLuckyNumber > this->crossOverProb){
        //it does not perform crossver, the new genes are kept the same of the previous interaction
        for(int i=0; i<this->chromossomeSize; i++){
            this->population[iInd]->setChromossomeAux(i, this->population[iInd]->getGene(i));
        }
    }else{//it must do crossver
        for(int i=0; i<chromossomeSize; i++){
            double newGene = fabs(this->crossOverBLXAlpha(
                    this->population[p1]->getGene(i),
                    this->population[p2]->getGene(i)));
            this->population[iInd]->setChromossomeAux(i, newGene);
        }
    }
}

/**
 * performs the crossover and mutation for a single generation
 */
void GeneticAlgorithm::generation(){
    ///Ignores the first elements - since they are the elite they are not changed
    for(int i=this->elite; i<this->populationSize; i++)
    {
        //Selecione 2 pais em P
        int parent1 = this->rankSelection(-1);//-1 means we can choose any parent
        int parent2 = this->rankSelection(parent1); //chose anyone but the first parent again
        //create a new guy from crossover
        this->crossOver(parent1, parent2, i);
        //this->population[i]->mutate();
        this->population[i]->updateChromossome();
    }
}
/**
 *
 * Performs the population evolution
 */
void GeneticAlgorithm::evolution(){
    try{
        this->iniPopulation();
        for(generationCurrent=1;generationCurrent<=generationMax;generationCurrent++){
            //performs the crossovers and mutations
            this->generation();
            //computes the fitness (defined by user)

        }
    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
    }
}
/**
 * Starts the population with random numbers
 */
void GeneticAlgorithm::iniPopulation(){
    for(int i=0; i<this->populationSize; i++)
    {
        this->population.push_back(new Individual(i,
                                             this->generationMax,
                                             this->mutationProb, this->mutationB,
                                             this->populationSize, this->chromossomeSize,
                                             this->minAllele, this->maxAllele));
        this->population[i]->iniChromossome();
    }

}
