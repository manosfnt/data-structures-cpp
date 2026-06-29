#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;



//θα φτιαξουμε κλαση minheap με τους παρακατω μεθοδους 
class MINHEAP{
    private: 
        int size;
        int capacity; 
        int *heap;
        int parent(int i);
        int right(int i);
        int left(int i);
    public:
        MINHEAP(int capacity);
        ~MINHEAP();
        void insert(int element);
        void ensureheap(int i);//aka heapify
        int GETSIZE();
        int FINDMIN();
        bool isempty (); 
        bool isfull();
        int *getheap();
        void deletemin();
        void resizeheap(int newcapacity);
        void buildheap(int* arr, int n);
        void printheap(ofstream &output);

};















#endif 