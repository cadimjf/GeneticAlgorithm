#include "AntColony.h"
/**
 * This code is an implementation of Ant colony optimizations for continous problems.
 * It is based on the work of  
 * Socha, K., 2009. Ant colony optimisation for continuous and mixed-variable domains. Saarbrücken: VDM Publishing.
 *

 */
AntColony::AntColony(int numParam, int nAnts, int numArchive, int itNumber, double q, double(*function_ptr_fitness)(vector<double>) ):
        OptimizationMethod(itNumber, function_ptr_fitness)
{
        //Set parameters, initialize pheromone trails
        //the population is divided in two slices:
        //from 0 to numArchieve - 1: The solution archieve
        //from numArchieve to numArchieve+nAnts-1: the temporary solutions to each ant
        this->population = new Population<Individual*>(nAnts+numArchive, numParam);
        this->sumWeight = 0.0;
        this->iterationCurrent=0;
        this->nAnts = nAnts;
        this->numArchive = numArchive;
        this->q = q;
        this->setStopCriteria(0.0001);
        for(int i=0; i<this->population->getSize(); i++) {
            SolutionArchive *ind = new SolutionArchieve(i,
                                             numParam,
                                            this->evaluation_function);
            this->population->insertPopulationItem(ind);
        }
        //random start new solution
        this->population->initialize();
        this->fitness(0, this->population->getSize());
        this->weights();
        this->probabilities();
}
/**
 * computes fitnes of a given slice of population
 */
void AntColony::fitness(int ini, int end){
        for(int j=ini;j<end;j++){
                this->population->popItems.at(j)->fitness();
        }
        //orders the population according to fitness (all the population is sorted)
        this->population->quickSort(0, this->population->getSize()-1);
}

void AntColony::weights(){
        this->sumWeight = 0.0;
        //the weights can be computed only for solutions within the solution archieve.
        for(int j=0; j<numArchive; j++){
                sumWeight += this->population->computeWeight(this->numArchive, j,  this->q);
        }
}
void AntColony::probabilities(){
        for(int j=0; j<numArchive; j++){
                this->population->computeProbability(this->sumWeight);
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
AntColony::search(){
        //compute the evaluation
        double newEvaluation = this->population->popItems.at(0)->evaluate();
        //accept the new parameters
        this->population->popItems.at(0)->updateParameters();
        double bestEvaluation=newEvaluation;

        iterationCurrent=1;
        do{
                // construct ant solutions
                //daemon actions local search 
                // update pheromones
                iterationCurrent++;
                if(bestEvaluation<=this->getStopCriteria()){
                        cout<<"Reached the stop criteria: "<<this->getStopCriteria()<<endl;
                        break;
                }
        }while(iterationCurrent<iterationsNumber);
        cout<<"Evaluation: "<<bestEvaluation<<endl;
        cout<<"Iterations : "<<iterationCurrent<<endl;
        this->population->popItems.at(0)->print();       
}