//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>

#include "../Common/ParameterSet.h"
#include "../Common/MyUtil.h"
#if defined(__linux__)
#define barra "/" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#else
#define barra "\\"
#endif

using namespace std;

class Individual : public ParameterSet{
public:
    Individual(int i, int cs, double mutationProb,  int mutType,
               double(*func_fit)(vector<double>));
    ~Individual();
    void  mutate(int gen, int genMax,double b);
    double getGene(int i);
    void computeFitness();
    void printInfo();

private:
    int mutType;
    double   uniformMutation(int i);
    double   nonUniformMutation(int i, int gen, int genMax,double b);
    double   delta(double y,int gen, int genMax,double b);
    double mutationProb;
};

#endif //GENETICALGORITHM_INDIVIDUAL_H
