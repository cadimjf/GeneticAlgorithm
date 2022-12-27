//
// Created by ricar on 26/12/2022.
//

#include "MyUtil.h"
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