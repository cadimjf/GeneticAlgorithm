//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Random.h"
#include "Individual.h"
#include "MyUtil.h"
class GeneticAlgorithm {
public:
    GeneticAlgorithm(int cs, int nPopulation, int gm);
    void setElite(int);
    void setCrossOverProb(double);
    void setThreadsNumber(int);
    void setAlpha(double);
    void setMutationB(double);
    void setMutationProb(double);
    void evolution();
    void setMinAllele(int i, double val);
    void setMaxAllele(int i, double val);
private:
    void iniAlleleBoundaries();
    void iniPopulation();
    unsigned    agSeed;
    int         elite; //number of individuals kept in the next generation
    int         populationSize;
    int         generationCurrent;
    int         generationMax;

    double      sumFit;
    double      avgFitness;

    int         iBest;
    int         iWorst;
    default_random_engine agRandomGenerator;
    double      crossOverProb;
    int         numThreads;
    double      alpha;
    double      mutationB;
    double      mutationProb;
    Individual  **population;
    double *maxAllele;
    double *minAllele;
    int chromossomeSize;
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
