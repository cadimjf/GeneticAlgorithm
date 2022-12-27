//
// Created by ricar on 26/12/2022.
//

#ifndef GENETICALGORITHM_MYUTIL_H
#define GENETICALGORITHM_MYUTIL_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;


struct MyException : public std::exception
{
    std::string msg;
    std::string fileName;
    int lineNumber;
    MyException(std::string ss, std::string fn, int l){
        this->msg          = ss;
        this->fileName     = fn;
        this->lineNumber   = l;
    }
    ~MyException() throw () {} // Updated
    const char* what() const throw() {
        stringstream ss;
        ss<<"Error in file "<<this->fileName<< " at line "<<this->lineNumber<<":"<<endl;
        ss<<"\t"<<this->msg;
        string str = ss.str();
        return str.c_str();
    }
    std::string getMessage() {
        stringstream ss;
        ss<<"Error in file "<<this->fileName<< " at line "<<this->lineNumber<<":"<<endl;
        ss<<"\t"<<this->msg;
        return ss.str();

    }
};


template< typename T > T* myAllocation( int length )
{
    T* al = (T*) malloc(length * sizeof(T));
    if(al==NULL) throw ("Allocation Failure", __FILE__, __LINE__);
    else  return al;
}

template< typename T > T** myArrayAllocation( int length )
{
    T** array = (T**) malloc(length*sizeof(T*));
    if(array==NULL){
        throw MyException("Allocation Failure", __FILE__, __LINE__);
    }else{
        for(int i=0;i<length;i++){
            array[i] =  (T*) malloc(sizeof(T));
        }
        return array;
    }
}

template< typename T > void myArrayDeallocation(T** array, int length )
{
    for(int i=0;i<length;i++){
        if(array[i]!=NULL) free(array[i]);
    }
    if(array!=NULL) free(array);
}

#endif //GENETICALGORITHM_MYUTIL_H
