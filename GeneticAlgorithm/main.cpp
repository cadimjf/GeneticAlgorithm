#include <iostream>
#include "GeneticAlgorithm.h"
int main() {
    GeneticAlgorithm *ga = new GeneticAlgorithm(5, 5, 10);
    //ga->setMutationProb(0.1);
    ga->setElite(1);
    std::cout << "Hello, World!er" << std::endl;
    ga->setMaxAllele(0, 10);
    ga->setMinAllele(1, 10000);
    ga->setMaxAllele(1, 20000);
    ga->evolution();
    delete(ga);
    cout<<"apaguei memo"<<endl;
    return 0;
}
