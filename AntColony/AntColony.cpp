#include "AntColony.h"
/**
 *
 * This code is an implementation of Ant colony optimizations for continous problems.
 * It is based on the work of
 * Socha, K., 2009. Ant colony optimisation for continuous and mixed-variable domains. Saarbrücken: VDM Publishing.
 *
 * @param numParam
 * @param nAnts
 * @param archiveSize
 * @param itNumber
 * @param function_ptr_fitness
 */
AntColony::AntColony(int numParam, int nAnts, int archiveSize, int itNumber, double(*function_ptr_fitness)(vector<double>) ):
        OptimizationMethod(itNumber, function_ptr_fitness)
{

    //Set parameters, initialize pheromone trails
    //the population is divided in two slices:
    //from 0 to archiveSize - 1: The solution archieve
    //from archiveSize to archiveSize+nAnts-1: the temporary solutions to each ant
    this->population = new Population<SolutionArchive*>(nAnts+archiveSize, numParam);
    this->sumWeight = 0.0;
    this->iterationCurrent=0;
    this->nAnts = nAnts;
    this->archiveSize = archiveSize;
    this->localitySearchProcess = 1.e-1;
    this->speedConvergence = 0.85;

    this->setStopCriteria(0.0001);
    for(int i=0; i<this->population->getSize(); i++) {
        SolutionArchive *ind = new SolutionArchive(i,
                                         numParam,
                                        this->evaluation_function);
        this->population->insertPopulationItem(ind);
    }
    //random start new solution
    this->population->initialize();
}
AntColony::~AntColony() {
    delete( this->population);
}

/**
 * computes fitnes of a given slice of population
 */
void AntColony::fitness(int ini, int end){
    for(int j=ini;j<end;j++){
        this->population->popItems.at(j)->getFitness();
    }

}
/**
 *
 */
void AntColony::weights(){
    this->sumWeight = 0.0;
    //the weights can be computed only for solutions within the solution archieve.
    for(int j=0; j<archiveSize; j++){
        sumWeight += this->population->popItems.at(j)->computeWeight(this->archiveSize, j,  this->localitySearchProcess);
    }
}
/**
 *
 */
void AntColony::probabilities(){
    for(int j=0; j<archiveSize; j++){
        this->population->popItems.at(j)->computeProbability(this->sumWeight);
    }
}
/**
while termination conditions not met do
        ConstructAntSolutions
        daemons actions ApplyLocalSearch {optional}
        UpdatePheromones
end while

The basic flow of the ACOR algorithm is as follows. As a first step, the solution archive is
initialized. Then, at each iteration, a number of solutions is probabilistically constructed
by the ants. These solutions may be improved by any improvement mechanism (for
example, local search or gradient techniques). Finally, the solution archive is updated
with the generated solutions. In the following we outline the components of ACOR in
more details.
*/
void AntColony::search(){
    //computes the initial fitness, weights and probabilities
    this->fitness(0, this->population->getSize());
    //orders the population according to fitness (all the population is sorted)
    this->population->quickSort(0, this->population->getSize()-1);
    //computes weights and probabilities
    this->weights();
    this->probabilities();
    iterationCurrent=1;
    do{
        // construct ant solutions
        this->antConstructSolutions(); //creates new solution on the corresponding ants positions

        //daemon actions local search
        // update pheromones
        this->pheromones();

        iterationCurrent++;
        if(this->population->popItems.at(0)->getEvaluationValue() <=  this->getStopCriteria()){
            cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
            break;
        }
    }while(iterationCurrent<iterationsNumber);
    cout<<"Evaluation "<<population->popItems.at(0)->getEvaluationValue()<<endl;
    cout<<"Iterations : "<<iterationCurrent<<endl;
    this->population->popItems.at(0)->print();
}
/***
 * computes the initial fitness, weights and probabilities
 */
void AntColony::pheromones(){
    //computes fitness on the new solution constructed by ants
    this->fitness(this->archiveSize, this->population->getSize());
    //orders the population according to fitness (all the population is sorted)
    this->population->quickSort(0, this->population->getSize()-1);
    /*for(int j=0;j<this->population->getSize();j++)
        cout<<j<<":"<<population->popItems.at(j)->getEvaluationValue()<<" ";
    cout<<endl;
    getchar();*/
    //computes new weights and probabilities
    this->weights();
    this->probabilities();
}
/**
 *
 * @return
 */
int AntColony::antSelectSolution(){
    double myLuckNumber = doubleRandom(0.0, 1.0, &this->randomGenerator);
    double sumProb=0.0;
    for(int j=0;j<this->archiveSize;j++){
        sumProb += this->population->popItems.at(j)->getProbability();
        if(sumProb > myLuckNumber){
            return j;
        }
    }
    return archiveSize-1;
}
/***
 *
 * @param jArchieve
 * @param iParam
 * @return
 */
vector<double> AntColony::antSolutionDistances(int jArchive){
    //create a vector and initialize with 0s
    vector<double> distances(this->population->getParameterSetSize(), 0.0);

    for(int i=0; i<this->population->getParameterSetSize(); i++) {
        double si_jarchive = this->population->popItems.at(jArchive)->getParameter(i);
        for(int j=0;j<this->archiveSize;j++){
            double sij = this->population->popItems.at(j)->getParameter(i);
            distances.at(i) = distances.at(i) + fabs(sij - si_jarchive);
        }
        distances.at(i) = distances.at(i) / (this->archiveSize - 1);
    }
    return distances;

}
/**
 *
 * @param jArchieve
 * @param iParam
 * @return
 */
vector<double> AntColony::antSigma(int jArchive){
    vector <double> dist = this->antSolutionDistances(jArchive);
    for(int i=0; i<this->population->getParameterSetSize(); i++) {
        dist.at(i) = dist.at(i) * this->speedConvergence;
    }
    return dist;
}
/**
 * @param sigma
 * @param mi
 * @param x
 * @return
 */
double AntColony::antGaussianFunction(double sigma, double mi, double x){
    return (1./sigma*sqrt(2.*M_PI))*exp(-powf(x-mi, 2.)/(2.*sigma*sigma));
}
/**
 *
 * @param sigma
 * @param mi
 * @param x
 * @return
 */
double AntColony::antProbabilityDensityFunction(double sigma, double mi, double x){
    return this->antGaussianFunction(sigma, mi, x);
}
/**
 *
 * @return
 */
vector<double> AntColony::antMeans(){
    //create a vector and initialize with 0s
    vector<double> means(this->population->getParameterSetSize(), 0.0);

    for(int i=0; i<this->population->getParameterSetSize(); i++) {
        for(int j=0;j<this->archiveSize;j++){
            means.at(i) = means.at(i) + this->population->popItems.at(j)->getParameter(i);
        }
        means.at(i) = means.at(i) / (this->archiveSize);
    }
    return means;
}
/**
 *
 * @param jArchive
 */
void AntColony::antNewSolution(int jArchive, int iAnt, vector<double> mi){
    vector<double> sigma = this->antSigma(jArchive);

    for(int i=0; i<this->population->getParameterSetSize(); i++) {
        double oldParam = this->population->popItems.at(jArchive)->getParameter(i);
        double newParam = oldParam * antProbabilityDensityFunction(sigma.at(i), mi.at(i), oldParam);
        //puts the new value on the respective ant position
        this->population->popItems.at(archiveSize + iAnt)->setParameterAux(i, newParam);
    }

}

/**
 *
 */
void AntColony::antConstructSolutions(){
    vector<double> mi    = this->antMeans();
    for(int j=0; j<this->nAnts; j++){
        //select a solution from archive
        int selectedSolution = this->antSelectSolution();
        //create a new solution archiveSize + j
        this->antNewSolution(selectedSolution, j, mi);
    }
}
