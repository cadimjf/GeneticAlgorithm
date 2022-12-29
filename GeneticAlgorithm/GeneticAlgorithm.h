//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include "../Common/Random.h"
#include "../Common/Population.h"
#include "Individual.h"
#include "../Common/MyUtil.h"
#include "../Common/OptimizationMethod.h"
using namespace std;

class GeneticAlgorithm: public OptimizationMethod{
public:
    GeneticAlgorithm(int cs, int nPopulation, int gm, double(*func_ptr_fit)(vector<double>));
    ~GeneticAlgorithm();
    void setElite(int);
    void setCrossOverProb(double);
    void setAlpha(double);
    void setMutationB(double);
    void setMutationProb(double);
    void search();
    void setMutationNonUniform();
    void setMutationUniform();
    void setSelectionRouletteWheel();
    void setSelectionRank();
    Population<Individual*> *population;
private:

    int mutationType;
    int selectionType;

    int         elite; //number of individuals kept in the next generation
    double      crossOverProb;
    double      alpha;
    double      mutationB;
    double      mutationProb;
    void computeFitness(int i0);
    void generation();
    int rankSelection(int forbidenGuy);
    int rouletteWheelSelection(int forbidenGuy);
    double sumRank;
    void crossOver(int p1, int p2, int iInd);
    double crossOverBLXAlpha(double gene1, double gene2);
    void selection(int *p1, int *p2);
    double      sumFit;
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
