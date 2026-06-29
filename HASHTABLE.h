#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "List.h"
#include <fstream>
#include <iostream>
using namespace std;
class HashTable{
    protected:
        List *htable;
        int HashGroups;
        int currentHashGroups;
        int hashingfuction(int key);
        const float LoadFactor();
        void resize();
        const int mult=2;//κατα ποσο αυξανεται το μεγεθος το hashtable
        const float LFlimit=0.9;//Mεχρι ποσο μπορει να γεμισει
    public:
        HashTable(int Hashgroups);
        ~HashTable();
        int getHashGroups();
        void insert(int key);
        bool search(int key);
        void BuildHashTable(int *A,int n);
        void printHashTable(ofstream &output);

};
#endif 
   