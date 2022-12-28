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
    Individual(int i, double mutationProb,  int cs, int mutType,
               vector<double> min, vector<double> max, double(*func_ptr_fit)(vector<double>));
    virtual ~Individual();

    void  mutate(int gen, int genMax,double b);
    void    setGeneration(int);
    int     getId();
    void    iniChromossome();
    void changeBounds(int iChron, double min, double max);
    double getGene(int i);
    void updateChromossome();
    void setChromossomeAux(int i, double val);
    double getFitness();

    double getChromossomeAux(int);
    void computeFitness();
    void printInfo();
private:
    int mutType;
    double   fitness;
    double(*function_ptr_fitness)(vector<double>);
    double  uniformMutation(int i);
    double   nonUniformMutation(int i, int gen, int genMax,double b);
    double   delta(double y,int gen, int genMax,double b);
    default_random_engine individualRandomGenerator;
    vector<double> chromosomeAUX;
    Chromosome *chromosome;
    int chromosomeSize;
    int     id;
    double mutationProb;



};

#endif //GENETICALGORITHM_INDIVIDUAL_H
