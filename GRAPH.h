#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>
#include <sstream>
#include <string>
#include  <iostream>
#include "FUCTIONS.h"
using namespace std;
#include "HASHTABLE.h"
#include "MINHEAP.h"
struct Edge{
    int weight;
    int destV;
    Edge *next;
    Edge() : destV(0), weight(0), next(nullptr) {
    }
    Edge(int destination ,int weight):destV(destination),weight(weight),next(nullptr){
    }
};
class Graph:public Edge {
    private :
        int Verts;
        int Edges;
        HashTable hashtable;
        Edge **adjMatrix;//δυδιαστατος πινακας
    public:
    Graph();
    ~Graph();
    int getEdges();
    int getVerts();
    Edge* existingEdge(int source,int destination);
    void BuildGraph(string comm3);
    void insertEdge(int source,int destination,int weight);
    void deleteEdge(int source,int destination);
    //αλγοριθμοι
    int computeShortestPath(int source,int destination);
    int computeSpanningTree();
    int findConnectedComponents();
    //βοηθητικες
    void DFSalgo(int e,bool *s);
    void printGraph(ofstream &output);



};
#endif
