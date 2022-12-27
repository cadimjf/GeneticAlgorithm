//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_GENE_H
#define GENETICALGORITHM_GENE_H


class Gene {
private:
    int id;
    double allele;
    double alleleMax;
    double alleleMin;
public:
    Gene(double min, double max);
    void setAllele(double);
    void setAlleleMax(double);
    void setAlleleMin(double);
    int getId(){return id;}
    double getAllele(){return allele;}
    double getAlleleMax(){return alleleMax;}
    double getAlleleMin(){return alleleMin;}
};


#endif //GENETICALGORITHM_GENE_H
