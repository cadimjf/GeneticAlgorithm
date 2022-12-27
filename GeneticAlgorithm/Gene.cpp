//
// Created by ricar on 26/12/2022.
//

#include "Gene.h"
/**
 * Constructor
 * starts a gene with its max and min boudaries
 * @param min
 * @param max
 */
Gene::Gene(double min, double max){
    this->setAlleleMax(max);
    this->setAlleleMin(min);
    this->setAllele(0);
}
/**
 *  set the max boundary for the gene
 * @param max
 */
void Gene::setAlleleMax(double max){
    this->alleleMax = max;
}
/**
 *  set the min boundary for the gene
 * @param min
 */
void Gene::setAlleleMin(double min){
    this->alleleMin = min;
}
/**
 *
 * @param a
 */
void Gene::setAllele(double a){
    this->allele = a;
}