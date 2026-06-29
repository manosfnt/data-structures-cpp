#include "MINHEAP.h"
#include <iostream>
#include <fstream>
using namespace std;
/*
@return το γονεα του στοιχειου i
*/
int MINHEAP::parent(int i){
    return (i-1)/2;
}
/*
@return το δεξιο παιδι του στοιχειου i
*/
int MINHEAP::right(int i){
    return 2*i+2;
}
/*
@return το αριστερο παιδι του στοιχειου i
*/
int MINHEAP::left(int i){
    return 2*i+1;
}
/*
@brief   κατασκευαστης του σωρου 
@param capacity ο αρχικος χωρος του σωρου
*/
MINHEAP::MINHEAP(int capacity) : heap(new int[capacity]), size(0), capacity(capacity){}
    
/*
@brief  καταστροφη του σωρου
*/
MINHEAP::~MINHEAP(){
    delete[] heap;
}
/*
@brief  ελεγχω αν ο σωρος ειναι κενος
@return true αν ο σωρος ειναι κενος, false αλλιως
*/
bool MINHEAP::isempty(){
    return size==0;
}
/*
@brief  ελεγχω αν ο σωρος ειναι γεματος
@return true αν ο σωρος ειναι γεματος, false αλλιως
*/
bool MINHEAP::isfull(){
    return size==capacity;
}
/*
@return το μεγεθος του σωρου
*/
int MINHEAP::GETSIZE(){
    return size;
}
/*
@return τον πινακα του σωρου
*/
int *MINHEAP::getheap(){
    return heap;
}   
/*
@brief  βρισκω το ελαχιστο στοιχειο του σωρου!!
@return το ελαχιστο στοιχειο του σωρου
*/
int MINHEAP::FINDMIN(){
    if (!isempty()){
        return heap[0];
    }
    else{
        return -1;
    }
}
/*
@brief  διαγραφω το ελαχιστο στοιχειο του σωρου και μειωνω το μεγεθος του
*/
void MINHEAP::deletemin(){
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
void MINHEAP::resizeheap(int newcapacity){
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
@param element το στοιχειο που εισαγεται
*/
void MINHEAP::insert(int element){
    if(isfull()){
        resizeheap(2*capacity);
    }
    heap[size]=element;
    size++;
    int i=size-1;
    while( i!=0 && heap[parent(i)]>heap[i]){
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
void MINHEAP::ensureheap(int i){
    int l=left(i);
    int r=right(i);
    int small=i;
    if ((l<size)&& (heap[l]<heap[small])){
        small=l;
    }
    if ((r<size)&& (heap[r]<heap[small])){
        small=r;
    }
    if (small!=i){
        int temp=heap[i];
        heap[i]=heap[small];
        heap[small]=temp;
        ensureheap(small);   
    }

}
/*
@brief εμφανιζω τον σωρο σε αρχειο
@param output  το αρχειο που εμφανιζω τον σωρο
*/
void MINHEAP::printheap(ofstream &output){
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
    void MINHEAP::buildheap(int *arr, int n){
        for (int i = 0; i < n; i++){
            heap[i] = arr[i];
        }
        this->size = n;
        for (int i = (size - 1) / 2; i >= 0; i--){
            ensureheap(i);
        }
    }
    
    

    
    
