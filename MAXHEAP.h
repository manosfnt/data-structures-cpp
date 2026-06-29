#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

class MAXHEAP{
    private: 
        int size; 
        int capacity;
        int *heap;
        int parent(int i);
        int right(int i);
        int left(int i);
    public:
        MAXHEAP(int capacity);
        ~MAXHEAP();
        void insert(int element);
        void ensureheap(int i);//aka heapify
        int GETSIZE();
        int FINDMAX();
        bool isempty (); 
        bool isfull();
        int *getheap();
        void deletemax();
        void resizeheap(int newcapacity);
        void buildheap(int* arr, int n);
        void printheap(ofstream &output);

};
#endif