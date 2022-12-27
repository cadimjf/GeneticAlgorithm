//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include "Random.h"
#include "Chromosome.h"
#include "MyUtil.h"
#if defined(__linux__)
#define barra "/" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#else
#define barra "\\"
#endif

using namespace std;

class Individual {
public:
    Individual(int i, int generationMax, double mutationProb, double mutationB, int pS, int cs,
               vector<double> min, vector<double> max, double(*func_ptr_fit)(vector<double>));
    virtual ~Individual();

    void  mutate(int gen);
    void    setGeneration(int);
    int     getId();
    void    iniChromossome();
    double   fitness;
    void changeBounds(int iChron, double min, double max);
    int fitnessRank;
    int populationSize;
    double getGene(int i);
    void updateChromossome();
    void setChromossomeAux(int i, double val);
    double getFitness();

    double getChromossomeAux(int);
    void computeFitness();
private:

    double(*function_ptr_fitness)(vector<double>);
    double  uniformMutation(int i);
    double   nonUniformMutation(int i, int gen);
    double   delta(double y,int gen);
    default_random_engine individualRandomGenerator;
    vector<double> chromosomeAUX;
    Chromosome *chromosome;
    int chromosomeSize;
    int     id;
    double   b;
    int     maxGeneration;
    double mutationProb;



};

#endif //GENETICALGORITHM_INDIVIDUAL_H
