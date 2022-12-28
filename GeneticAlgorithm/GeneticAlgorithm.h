//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include "../Common/Random.h"
#include "Individual.h"
#include "../Common/MyUtil.h"
#include "../Common/OptimizationMethod.h"
using namespace std;
class GeneticAlgorithm : public OptimizationMethod{
public:
    GeneticAlgorithm(int cs, int nPopulation, int gm, double(*func_ptr_fit)(vector<double>));
    ~GeneticAlgorithm();
    void setElite(int);
    void setCrossOverProb(double);
    void setAlpha(double);
    void setMutationB(double);
    void setMutationProb(double);
    void evolution();
    void setStopCriteria(double s){stopCriteria=s;}
    double getStopCriteria(){return stopCriteria;}
    void setMutationNonUniform();
    void setMutationUniform();
private:
    int mutationType;
    double stopCriteria;
    void iniPopulation();

    int         elite; //number of individuals kept in the next generation
    int         populationSize;
    int         generationCurrent;
    int         generationMax;

    double      sumFit;
    double      avgFitness;

    default_random_engine agRandomGenerator;
    double      crossOverProb;
    double      alpha;
    double      mutationB;
    double      mutationProb;
    std::vector<Individual*> population;

    void computeFitness(int i0);

    void generation();
    int rankSelection(int forbidenGuy);
    double sumRank;
    void crossOver(int p1, int p2, int iInd);
    double crossOverBLXAlpha(double gene1, double gene2);
    int partitionQckSort(int p, int r);
    void quickSort( int p, int r);

};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
