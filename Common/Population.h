//
// Created by ricar on 29/12/2022.
//

#ifndef GENETICALGORITHM_GENERICPOPULATIONTEMPLATE_H
#define GENETICALGORITHM_GENERICPOPULATIONTEMPLATE_H


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace  std;
template <class genericPop>
    class Population{
    public:
        vector<genericPop> popItems;
        Population (int popSize, int paramNum){
            this->populationSize  = popSize;
            this->parameterSetSize = paramNum;
        };
        ~Population(){this->popItems.clear(); };

        void setMaxParameter(int i, double val){
            for (int ind = 0; ind < this->populationSize; ind++) {
                popItems.at(ind)->setMaxParameter(i, val);
            }
        };

        void initialize(){
            for(int i=0; i<this->populationSize; i++){
                this->popItems.at(i)->iniParameters();
            }
        };
        void setMinParameter(int i, double val){
            for(int j=0;j<populationSize;j++){
                this->popItems.at(j)->setMinParameter(i, val);
            }
        };
        int partitionQckSort(int p, int r){
            double pivot = this->popItems.at(r)->getEvaluationValue();
            int i = p-1;
            for(int j=p;j<r;j++){
                if(this->popItems.at(j)->getEvaluationValue()<=pivot){
                    i++;
                    genericPop aux     = this->popItems.at(i);
                    this->popItems.at(i) = this->popItems.at(j);
                    this->popItems.at(j) = aux;
                }
            }
            genericPop aux     = this->popItems.at(i+1);
            this->popItems.at(i+1) = this->popItems.at(r);
            this->popItems.at(r) = aux;
            return i+1;
        };
        void quickSort( int p, int r){
            if ( p < r ){
                int j = this->partitionQckSort(p, r);
                quickSort(p, j-1);
                quickSort(j+1, r);
            }
        };
        void insertPopulationItem(genericPop item){
            this->popItems.push_back(item);
        };
        int getSize(){return populationSize;};
        int getParameterSetSize(){return parameterSetSize;};
        void makeNoise(){
            double newParam = 0.0;
            for(int i=0; i<this->popItems.at(0)->getParametersNum();i++){
                //the interval is from -noise : +noisa
                newParam = this->popItems.at(0)->getRandomDouble(getMinNewParameter(i), getMaxNewParameter(i));
                //cout<<getMinNewParameter(i)<<" "<<newParam<<" "<<getMaxNewParameter(i)<<endl;
                this->popItems.at(0)->setParameterAux(i, newParam);
            }
        };
        void setNoise(double n){noise=n;};
        double getNoise(){return noise;};
    private:
        int populationSize;
        int parameterSetSize;
        double noise;

        double getMinNewParameter(int i){
            double parameterNoised = this->popItems.at(0)->getParameter(i) - this->getNoise();
            if (parameterNoised<this->popItems.at(0)->getMinParameter(i)){
                return this->popItems.at(0)->getMinParameter(i);
            }else{
                return parameterNoised;
            }
        };
        double getMaxNewParameter(int i){
            double parameterNoised = this->popItems.at(0)->getParameter(i) + this->getNoise();
            if (parameterNoised > this->popItems.at(0)->getMaxParameter(i)){
                return this->popItems.at(0)->getMaxParameter(i);
            }else{
                return parameterNoised;
            }
        };


    };

#endif //GENETICALGORITHM_GENERICPOPULATIONTEMPLATES_H





