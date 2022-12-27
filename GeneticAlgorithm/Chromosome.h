//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_CHROMOSOME_H
#define GENETICALGORITHM_CHROMOSOME_H

#include <stdio.h>
#include <math.h>
#include "Gene.h"
#include "MyUtil.h"
using namespace std;

class Chromosome {
private:
    Gene   **genes;
    int chromosomeSize;
public:
    Chromosome(int, double *min, double* max);
    virtual ~Chromosome();
    void setAllele(int i, double val);
    double getMaxAllele(int);
    double getMinAllele(int);



};



#endif //GENETICALGORITHM_CHROMOSOME_H
