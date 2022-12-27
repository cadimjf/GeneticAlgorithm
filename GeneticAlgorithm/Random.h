/* 
 * File:   Compare.h
 * Author: ricardo
 *
 * Created on July 30, 2014, 10:19 PM
 */

#ifndef COMPARE_H
#define	COMPARE_H

#include <random>
#include <chrono>
#include <omp.h>
#include <stdio.h>

using namespace std;

double doubleRandom(double min, double max, default_random_engine *gen);
int intRandom(int min, int max, default_random_engine *gen);

#define EXP1 1 
#define EXP2 2 //transversely isotropic material
#define EXP3 3 //anysotropic material
#define FISIOPACER_FAILURE  -1.0
//#define WORSTFITNESS 100000.0

#endif	/* COMPARE_H */
