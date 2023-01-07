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
        OptimizationMethod(genNumber, function_ptr_fitness)
{
    try {
        this->population = new Population<Individual*>(nPopulation, chromoSize);
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
        this->sumRank = (this->population->getSize()+1)*this->population->getSize()/2;
        this->setMutationNonUniform();
        for(int i=0; i<this->population->getSize(); i++) {
            Individual *ind = new Individual(i,
                                             chromoSize,
                                            this->mutationProb,
                                            this->mutationType,
                                            this->evaluation_function);
            this->population->insertPopulationItem(ind);
        }
        //random start new solution
        this->population->initialize();
    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
    }
}
/**
 *
 */
GeneticAlgorithm::~GeneticAlgorithm(){
    delete(this->population);

}
/**
 *
 * @param forbidenGuy
 * @return
 */
int GeneticAlgorithm::rouletteWheelSelection(int forbidenGuy=-1){
    //numero da sorte, para escolher o individuo atraves de roleta
    double myLuckNumber = doubleRandom(0.0, this->sumFit, &this->randomGenerator);
    double sumFitness=0.0, myFitness=0.0;
    int selectedParent=-1;
    for(int i=0; i<this->population->getSize(); i++){
        myFitness = this->population->popItems.at(i)->getEvaluationValue();
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
    double partialSumRank=0.0;
    int selectedParent=-1;
    for(int i=0; i<this->population->getSize(); i++){
        //the greatest value is given to the best fitness in the population
        //and the least is given to the tha last individual - worst fitness
        partialSumRank += (this->population->getSize()-i);
        if(partialSumRank>=myLuckNumber  && forbidenGuy!=i){//we found our guy
            selectedParent= i;
            break;
        }
    }
    //if the forbidden guy is the las and no one was selected:
    if(forbidenGuy==this->population->getSize()-1 && selectedParent-1){
        selectedParent = intRandom(0, forbidenGuy-2, &this->randomGenerator);
    }
    if(selectedParent==-1) {
        //If we got here, no one was select. Exception!

        cout << "Fthis->sumRank " << this->sumRank << endl;
        cout << "Forbiden guy " << forbidenGuy << endl;
        cout << "myLuckNumber " << myLuckNumber << endl;
        cout << "partialSumRank " << partialSumRank << endl;
        throw MyException("No one was selected.", __FILE__, __LINE__);
    }else{
        return selectedParent;
    }

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
        for(int i=0; i<this->population->getParameterSetSize(); i++){
            double x = this->population->popItems.at(iInd)->getGene(i);
            this->population->popItems.at(iInd)->setParameterAux(i, x);
        }
    }else{//it must do crossver
        for(int i=0; i<this->population->getParameterSetSize(); i++){
            double newGene = fabs(this->crossOverBLXAlpha(
                    this->population->popItems.at(p1)->getGene(i),
                    this->population->popItems.at(p2)->getGene(i)));
            this->population->popItems.at(iInd)->setParameterAux(i, newGene);
        }
    }
}
void GeneticAlgorithm::selection(int *p1, int *p2){
    if(this->selectionType == SELECTION_RANK) {
        *p1 = this->rankSelection(-1);//-1 means we can choose any parent
        *p2 = this->rankSelection(*p1); //chose anyone but the first parent again
    }else if(this->selectionType == SELECTION_ROULETTEWHELL){
        *p1 = this->rouletteWheelSelection(-1);//-1 means we can choose any parent
        *p2 = this->rouletteWheelSelection(*p1); //chose anyone but the first parent again
    }else{
        throw MyException("Invalid selection type! ", __FILE__, __LINE__);
    }
}
/**
 * performs the crossover and mutation for a single generation
 */
void GeneticAlgorithm::generation(){
    ///Ignores the first elements - since they are the elite they are not changed
    for(int i=this->elite; i<this->population->getSize(); i++)
    {
        //Selecione 2 pais em P
        int parent1, parent2;
        this->selection(&parent1, &parent2);
        //create a new guy from crossover
        this->crossOver(parent1, parent2, i);
        //mutation
        this->population->popItems.at(i)->mutate(this->iterationCurrent, this->iterationsNumber, this->mutationB);
    }
}
/**
 *
 * @param i0
 */
void GeneticAlgorithm::computeFitness(int i0){
    this->sumFit = 0.0;
    for(int i=i0; i<this->population->getSize(); i++){
        this->population->popItems.at(i)->computeFitness();
        this->sumFit += this->population->popItems.at(i)->getEvaluationValue();
    }
    //orders the population according to the fitness
    this->population->quickSort(0, this->population->getSize()-1);
}

/**
 *
 * Performs the population evolution
 */
void GeneticAlgorithm::search(){
    try{
        //compute fitness with the initial populations
        this->computeFitness(0);
        iterationCurrent=1;
        do{
            //performs the crossovers and mutations
            this->generation();
            //computes the fitness
            this->computeFitness(this->elite);
            iterationCurrent++;
            //if the best individual fitness is less than the stop criteria, stops
            if(population->popItems.at(0)->getEvaluationValue()<=this->getStopCriteria()){
                cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
                break;
            }
        }while(iterationCurrent<iterationsNumber);

        cout<<"Finished evolution on generation "<<iterationCurrent<<endl;
        population->popItems.at(0)->printInfo();

    }catch(MyException& caught){
        std::cout<<caught.getMessage()<<std::endl;
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