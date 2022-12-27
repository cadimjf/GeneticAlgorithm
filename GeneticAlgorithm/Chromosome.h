//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_CHROMOSOME_H
#define GENETICALGORITHM_CHROMOSOME_H

#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <vector>
#include "Gene.h"
#include "MyUtil.h"

using namespace std;

class Chromosome {
private:
    std::vector<Gene*> genes;
    int chromosomeSize;
public:
    Chromosome(int, vector<double> min, vector<double> max);
    virtual ~Chromosome();
    void setAllele(int i, double val);
    double getMaxAllele(int);
    double getMinAllele(int);
    double getAllele(int i);


};



#endif //GENETICALGORITHM_CHROMOSOME_H
