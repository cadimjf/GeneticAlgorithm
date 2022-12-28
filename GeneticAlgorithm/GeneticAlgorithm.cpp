//
// Created by ricar on 26/12/2022.
//
#include "GeneticAlgorithm.h"

/***
 *
 * @param chromoSize
 * @param nPopulation
 * @param genNumber
 * @param function_ptr_fitness
 */
GeneticAlgorithm::GeneticAlgorithm(int chromoSize, int nPopulation, int genNumber, double(*function_ptr_fitness)(vector<double>) ):
        OptimizationMethod(chromoSize, genNumber, function_ptr_fitness)
{
    try {
        this->populationSize = nPopulation;
        this->sumFit = 0.0;
        this->iterationCurrent=0;
        this->setElite(4);
        this->setCrossOverProb(0.95);
        this->setAlpha(0.3);
        this->setMutationProb(0.05);
        this->setMutationB(3.0);
        this->setStopCriteria(0.0001);
        this->setSelectionRank();
        //used for rank selection - gives the sum of the position of all indivdual
        // 0 + 1 + 2 + ... + populationSize-1
        this->sumRank = (this->populationSize+1)*this->populationSize/2;
        this->setMutationNonUniform();
    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
    }
}
GeneticAlgorithm::~GeneticAlgorithm(){
    this->population.clear();

}

int GeneticAlgorithm::rouletteWheelSelection(int forbidenGuy=-1){
    //numero da sorte, para escolher o individuo atraves de roleta
    double myLuckNumber = doubleRandom(0.0, this->sumFit, &this->randomGenerator);
    double sumFitness=0.0, myFitness=0.0;
    int selectedParent=-1;
    for(int i=0; i<this->populationSize; i++){
        myFitness = this->population[i]->getFitness();
        sumFitness += (this->sumFit - myFitness);
        if(sumFitness>=myLuckNumber  && forbidenGuy!=i){//we found our guy
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
 * Select one individual for reproductions
 *  Rank selection
  * @param forbidenGuy avoids selecting the same individual to form parents
  * -1 indicates anyone can be choosen
 * @return
 */
int GeneticAlgorithm::rankSelection(int forbidenGuy=-1){
    //numero da sorte, para escolher o individuo atraves de roleta
    double myLuckNumber = doubleRandom(0.0, this->sumRank, &this->randomGenerator);
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
        cMax=gene2;
        cMin=gene1;
    }
    iMaxMin = cMax-cMin;
    return doubleRandom(cMin-iMaxMin*this->alpha, cMax+iMaxMin*this->alpha, &this->randomGenerator);

}

/**
 *
 * @param p1
 * @param p2
 * @param iInd
 */
void GeneticAlgorithm::crossOver(int p1, int p2, int iInd)
{
    double myLuckyNumber = doubleRandom(0.0, 1.0, &this->randomGenerator);
///if the parents are the same or the crossover is not done
    if(p1==p2 || myLuckyNumber > this->crossOverProb){
        //it does not perform crossver, the new genes are kept the same of the previous interaction
        for(int i=0; i<this->getParameterSetSize(); i++){
            double x = this->population[iInd]->getGene(i);
            this->population[iInd]->setParameterAux(i, x);
        }
    }else{//it must do crossver
        for(int i=0; i<this->getParameterSetSize(); i++){
            double newGene = fabs(this->crossOverBLXAlpha(
                    this->population[p1]->getGene(i),
                    this->population[p2]->getGene(i)));
            this->population[iInd]->setParameterAux(i, newGene);
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
        int parent1, parent2;
        if(this->selectionType == SELECTION_RANK) {
            parent1 = this->rankSelection(-1);//-1 means we can choose any parent
            parent2 = this->rankSelection(parent1); //chose anyone but the first parent again
        }else if(this->selectionType == SELECTION_ROULETTEWHELL){
            parent1 = this->rouletteWheelSelection(-1);//-1 means we can choose any parent
            parent2 = this->rouletteWheelSelection(parent1); //chose anyone but the first parent again
        }else{
            throw MyException("Invalid selection type! ", __FILE__, __LINE__);
        }
        //create a new guy from crossover
        this->crossOver(parent1, parent2, i);
        //mutation
        this->population[i]->mutate(this->iterationCurrent, this->iterationsNumber, this->mutationB);
    }
}
/**
 *
 * @param i0
 */
void GeneticAlgorithm::computeFitness(int i0){
    this->sumFit = 0.0;
    for(int i=i0; i<this->populationSize; i++){
        this->population[i]->computeFitness();
        this->sumFit += this->population[i]->getFitness();
    }
    //orders the population according to the fitness
    this->quickSort(0, this->populationSize-1);
}

/**
 *
 * Performs the population evolution
 */
void GeneticAlgorithm::search(){
    try{
        this->iniPopulation();
        //compute fitness with the initial populations
        this->computeFitness(0);
        for(iterationCurrent=1;iterationCurrent<=iterationsNumber;iterationCurrent++){
            //performs the crossovers and mutations
            this->generation();
            //computes the fitness
            this->computeFitness(this->elite);
            //if the best individual fitness is less than the stop criteria, stops
            if(population[0]->getFitness()<=this->getStopCriteria()){
                cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
                break;
            }
        }
        cout<<"Finished evolution on generation "<<iterationCurrent<<endl;
        population[0]->printInfo();
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
                                            this->mutationProb,
                                            this->getParameterSetSize(),
                                            this->mutationType,
                                            this->getMinParameterSet(), this->getMaxParameterSet(), this->evaluation_function));
        this->population[i]->iniParameters();
    }

}
/**
 * The partition function
 * @param input
 * @param p
 * @param r
 * @return
 */
int GeneticAlgorithm::partitionQckSort(int p, int r)
{
    double pivot = this->population[r]->getFitness();
    int i = p-1;
    for(int j=p;j<r;j++)
    {
        if(this->population[j]->getFitness()<=pivot){
            i++;
            Individual *aux     = this->population[i];
            this->population[i] = this->population[j];
            this->population[j] = aux;
        }
    }
    Individual *aux     = this->population[i+1];
    this->population[i+1] = this->population[r];
    this->population[r] = aux;
    return i+1;
}
/**
 * The quicksort recursive function
 * http://www.sourcetricks.com/2011/06/what-is-quick-sort-algorithm-how-to.html
 * @param p
 * @param r
 */
void GeneticAlgorithm::quickSort( int p, int r)
{
    if ( p < r )
    {
        int j = partitionQckSort(p, r);
        quickSort(p, j-1);
        quickSort(j+1, r);
    }
}
/**
 *
 */
void GeneticAlgorithm::setMutationNonUniform(){
    this->mutationType = MUTATION_NONUNIFORM;
}
void GeneticAlgorithm::setMutationUniform(){
    this->mutationType = MUTATION_UNIFORM;
}

void GeneticAlgorithm::setSelectionRouletteWheel(){
    this->selectionType = SELECTION_ROULETTEWHELL;
}
void GeneticAlgorithm::setSelectionRank(){
    this->selectionType = SELECTION_RANK;
}

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