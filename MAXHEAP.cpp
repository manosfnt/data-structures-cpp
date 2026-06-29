#include "MAXHEAP.h"
#include <iostream>
#include <fstream>
using namespace std;
/*
@return το γονεα του στοιχειου i
*/
int MAXHEAP::parent(int i){
    return (i-1)/2;
}
/*
@return το δεξιο παιδι του στοιχειου i
*/
int MAXHEAP::right(int i){
    return 2*i+2;
}
/*
@return το αριστερο παιδι του στοιχειου i
*/
int MAXHEAP::left(int i){
    return 2*i+1;
}
/*
@brief  κατασκευαστης του σωρου 
@param capacity ο αρχικος χωρος του σωρου
*/
MAXHEAP::MAXHEAP(int capacity){
    this->size=0;
    this->capacity=capacity;
    heap=new int[capacity];
    
}
/*
@brief  καταστροφη του σωρου
*/
MAXHEAP::~MAXHEAP(){
    delete[] heap;
} 
/*
@brief  ελεγχω αν ο σωρος ειναι κενος
@return true αν ο σωρος ειναι κενος, false αλλιως
*/
bool MAXHEAP::isempty(){
    return size==0;
}
/*
@brief  ελεγχω αν ο σωρος ειναι γεματος
@return true αν ο σωρος ειναι γεματος, false αλλιως
*/
bool MAXHEAP::isfull(){
    return size==capacity;
}
/*
@return το μεγεθος του σωρου
*/
int MAXHEAP::GETSIZE(){
    return size;
}
/*
@return τον πινακα του σωρου
*/
int *MAXHEAP::getheap(){
    return heap;
}
/*
@brief  βρισκω το μεγιστο στοιχειο του σωρου
@return το μεγιστο στοιχειο του σωρου
*/
int MAXHEAP::FINDMAX(){
    if (!isempty()){
        return heap[0];
    }
    else{
        return -1;
    }
}
/*
@brief  διαγραφω το μεγιστο στοιχειο του σωρου και μειωνω το μεγεθος του
*/
void MAXHEAP::deletemax(){
    if (!isempty()){
        if (size==1){
            size--;
        }
    else{
        heap[0]=heap[size-1];
        size--;
        ensureheap(0);
    }
        
    }

}
/*
@brief  αναπροσαρμοζω το μεγεθος του σωρου
@param newcapacity το νεο μεγεθος του σωρου
*/
void MAXHEAP::resizeheap(int newcapacity){
    int *temp=new int[newcapacity];
    for(int i=0;i<size;i++){
        temp[i]=heap[i];
        
    }
    delete[] heap;
    heap=temp;
    capacity=newcapacity;

}
/*
@brief  εισαγωγη στοιχειου στον σωρο και ελεγχω αν ειναι γεματος
@param element το στοιχειο που εισαγωγη
*/
void MAXHEAP::insert(int element){
    if(isfull()){
        resizeheap(2*capacity);
    }
    heap[size]=element;
    size++;
    int i=size-1;
    while( i!=0 && heap[parent(i)]<heap[i]){
        int temp=heap[i];
        heap[i]=heap[parent(i)];
        heap[parent(i)]=temp;
        i=parent(i);

    }
}
/*
@brief  ελεγχω αν ο πινακας ειναι σωρος(aka heapify)
@param i η θεση του στοιχειου που ελεγχω
*/
void MAXHEAP::ensureheap(int i){
    int l=left(i);
    int r=right(i);
    int big=i;
    if ((l<size)&& (heap[l]>heap[big])){
        big=l;
    }
    if ((r<size)&& (heap[r]>heap[big])){
        big=r;
    }
    if (big!=i){
        int temp=heap[i];
        heap[i]=heap[big];
        heap[big]=temp;
        ensureheap(big);   
    }

}
/*
@brief  εμφανιζω τον σωρο σε αρχειο
@param output το αρχειο που εμφανιζω τον σωρο
*/
void MAXHEAP::printheap(ofstream &output){
    if (output.is_open()){
        for (int i=0;i<size;i++){
            output<<heap[i]<<" ";
        }
        output<<endl;
    }
    else{
        cerr<<"could not open file"<<endl;
    }
            
        }
void MAXHEAP::buildheap(int *arr,int n){
     for (int i = 0; i < n; i++){
            heap[i] = arr[i];
        }
        this->size = n;
        for (int i = (size - 1) / 2; i >= 0; i--){
            ensureheap(i);
        }
}    

    
    

    
    
