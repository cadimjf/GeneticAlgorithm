//
// Created by ricar on 26/12/2022.
//

#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "../Common/Random.h"
#include "../Common/Population.h"
#include "../Common/MyUtil.h"
#include "../Common/OptimizationMethod.h"
#include "SolutionArchive.h"
using namespace std;

class AntColony: public OptimizationMethod{
public:

    AntColony(int numParam, int nAnts, int numArchive, int itNumber, double(*func_ptr_fit)(vector<double>));
    ~AntColony();
    Population<SolutionArchive*> *population;
    void search();

private:
    double sumWeight;
    int nAnts;
    int archiveSize;
    double localitySearchProcess; //q
    double speedConvergence;//ksi - evaporation rate
    void fitness(int, int);
    void weights();
    void probabilities();

    vector<double> antSolutionStdDev(vector<double> mi);
    vector<double> antSolutionDistances(int jArchive);
    vector<double> antSigma(int jArchive, vector<double>);
    vector<double> antMeans();
    double antGaussianFunction(double sigma, double mi, double x);
    double antProbabilityDensityFunction(double sigma, double mi, double x);
    void antNewSolution(int jArchive, int iAnt, vector<double>);
    void antConstructSolutions();
    int antSelectSolution();
    void pheromones(int, int);
};


#endif //ANTCOLONY_H
