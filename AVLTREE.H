#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <fstream>
using namespace std;
class AVLNode{//κλαση για τα κομβους του avl tree
    public:
        int key;
        AVLNode *left;
        AVLNode *right;
        int height;
        AVLNode(int k){
            key=k;
            left=right=nullptr;
            height=1;
        }
};
class AVLtree{
    private:
        AVLNode *root;
        int max(int a,int b);
        int height(AVLNode *n);
        int BalanceFactor(AVLNode *n);
        AVLNode *rightRotate(AVLNode *y);
        AVLNode *leftRotate(AVLNode *x);
    public:
        AVLtree();
        ~AVLtree(); 
        void setRoot(AVLNode *r);
        AVLNode* getRoot();
        AVLNode *minofsubtree(AVLNode *r);
        int getMin(AVLNode *r);
        int getSize(AVLNode *r);
        string search(AVLNode *r,int key);
        AVLNode *insert(AVLNode *r,int key);
        void inOrderTraversal(AVLNode *root, ofstream &output);
        AVLNode *deleteNode(AVLNode *r,int key);
        void buildAVLTree(int *arr,int size);
        void destroyTree(AVLNode* node);
};

#endif
