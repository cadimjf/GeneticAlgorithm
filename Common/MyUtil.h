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

#define MUTATION_UNIFORM 0
#define MUTATION_NONUNIFORM 1
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



#endif //GENETICALGORITHM_MYUTIL_H
