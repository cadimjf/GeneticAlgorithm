#include <iostream>
#include "GeneticAlgorithm.h"
int main() {
    GeneticAlgorithm *ga = new GeneticAlgorithm(5, 10, 10);
    std::cout << "Hello, World!er" << std::endl;
    ga->setMaxAllele(0, 10);
    ga->evolution();
    delete(ga);
    cout<<"apaguei memo"<<endl;
    return 0;
}
