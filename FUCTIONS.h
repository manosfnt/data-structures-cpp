#ifndef FUCTIONS_H
#define FUCTIONS_H
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
inline void enlargearray(int*& arr, int& capacity, int newCapacity) {
    int* newArr = new int[newCapacity];
    for (int i = 0; i < capacity && i < newCapacity; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}
//βοηθητική συνάρτηση που αλλαζει το μέγεθος του πίνακα
template <typename  X>
inline void enlargearray(X*&  arr,int &capacity,int morecapacity){
    X *newarr=new X[morecapacity];
    cout << "enlargearray: old capacity = " << capacity << ", new capacity = " << morecapacity << ", arr = " << (void*)arr << endl;
    for (int i=0;i<capacity;i++){
        newarr[i]=arr[i];
    }
    for (int i=capacity;i<morecapacity;i++){
        newarr[i]=X();
    }
    delete[] arr;
    arr=newarr;
    capacity=morecapacity;
   
};
 int  *integersfromfile(const string &comm3,int &size);
   

#endif