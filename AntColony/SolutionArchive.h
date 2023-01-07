//
// Created by ricar on 26/12/2022.
//

#ifndef ANTCOLONY_SOLUTION_ARCHIVE_H
#define ANTCOLONY_SOLUTION_ARCHIVE_H

#include "../Common/ParameterSet.h"
#include <math.h>

using namespace std;

class SolutionArchive: public ParameterSet{
public:
    SolutionArchive(int i, int cs, double(*func_fit)(vector<double>));
    ~SolutionArchive();
    double computeWeight(int k, int j, double q );
    double computeProbability(double);
    void getFitness();
    double getProbability();
    double getWeight();
private:
    double probability;
    double weight;



};


#endif //ANTCOLONY_SOLUTION_ARCHIVE_H
