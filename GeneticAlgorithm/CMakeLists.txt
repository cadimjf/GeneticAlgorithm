cmake_minimum_required(VERSION 3.24)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(GeneticAlgorithm main.cpp GeneticAlgorithm.cpp GeneticAlgorithm.h Chromosome.cpp Chromosome.h Individual.cpp Individual.h MyUtil.cpp MyUtil.h Gene.cpp Gene.h)
