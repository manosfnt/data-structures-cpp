#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <fstream>
using namespace std;
class Node{
    public:
        int key;
        Node*next;
        Node(int key){
            this->key=key;
            next=nullptr;
        }
};
class List{
    protected:
        Node *header;
    public:
        bool isEmpty();
        List();
        ~List();
        Node *getHeader();
        void insert(int key);
        bool search(int key);
        void printlist(ofstream &output);

} ;       
#endif 