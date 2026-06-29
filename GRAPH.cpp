#include "GRAPH.h"
#include <iostream>
#include <climits>
#include "FUCTIONS.h"
#define MAXelements 10000
using namespace std;
//@brief Κατασκευαστής του γράφου.Aρχικοποιεί τον πίνακα γειτνίασης και το hashtable
Graph::Graph():hashtable(15){ 
    Verts=0;
    adjMatrix=new Edge*[MAXelements];
    for(int i=0;i<MAXelements;i++){
        adjMatrix[i]=nullptr;
    } 
}
//@brief Καταστροφέας του γράφου.Eλευθερώνει όλη τη μνήμη των ακμών
Graph::~Graph(){
    for (int i=0;i<MAXelements;i++){
        Edge *temp=adjMatrix[i];
        while (temp!=nullptr){
            Edge *temp2=temp;
            temp=temp->next;
            delete temp2;
        }
    }
    delete[] adjMatrix;
}
//@return Επιστρέφει τον συνολικό αριθμό ακμών στον γράφο
int Graph::getEdges(){
    return Edges;
}
//@return Επιστρέφει τον συνολικό αριθμό κορυφών στον γράφο
int Graph::getVerts(){
    return  Verts;
}
/*
@brief Ελέγχει αν υπάρχει ήδη ακμή ανάμεσα σε δύο κόμβους
@param source η αρχική κορυφή
@param destination η τελική κορυφή
@return Επιστρέφει pointer στην ακμή αν υπάρχει,αλλιώς nullptr
*/
Edge *Graph::existingEdge(int source,int destination){
    Edge *temp=adjMatrix[source];
    while (temp!=nullptr){
        if (temp->destV==destination) return temp;
        temp=temp->next;
    }
    return nullptr;
}

/*
@brief Εισάγει μία ακμή μεταξύ δύο κόμβων
@param source η αρχική κορυφή
@param destination η τελική κορυφή
@param weight το βάρος της ακμής
*/   
void Graph::insertEdge(int source,int destination,int weight){
    if (existingEdge(source,destination)==nullptr){
        //ελεγχουμε αν υπαρχουν, αν οχι τοτε προθετουμε τα vertises στο hashtable και αυξανουμε τον αριθμο
        if (adjMatrix[source]==nullptr){
            hashtable.insert(source);
            Verts++;
        }
        if(adjMatrix[destination]==nullptr){
            hashtable.insert(destination);
            Verts++;
        }
        //βαζουμε τα edges απο το source στο destination και το αναποδο 
        Edge *connectingEdge= new Edge(source,weight);
        connectingEdge->next=adjMatrix[destination];
        adjMatrix[destination]=connectingEdge;
        connectingEdge=new Edge(destination,weight);
        connectingEdge->next=adjMatrix[source];
        adjMatrix[source]=connectingEdge;
            Edges++;
    }
}

/*
@brief Διαγράφει μία ακμή μεταξύ δύο κόμβων
@param source η αρχική κορυφή
@param destination η τελική κορυφή
*/
void Graph::deleteEdge(int source, int destination) {
    // Διαγραφή από τη λίστα του src
    Edge *prev = nullptr;
    Edge *curr = adjMatrix[source];
   
    while (curr != nullptr && curr->destV != destination) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != nullptr) {
        if (prev == nullptr) {
            adjMatrix[source] = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
    //Διαγραφή από τη λίστα του destination
    prev = nullptr;
    curr = adjMatrix[destination];
    while (curr != nullptr && curr->destV != source) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != nullptr) {
        if (prev == nullptr) {
            adjMatrix[destination] = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
    Edges--;
}
/*
@brief Δημιουργεί τον γράφο από αρχείο
@param name το όνομα του αρχείου εισόδου
*/
void Graph::BuildGraph(string name){
    int *arr=new int[100];
    int size=0;
    int capacity=100;
    
    int n1,n2,weight;
    string fileline;
    ifstream file(name);
    if (file.is_open()){
        while (getline(file,fileline)){
           if (size==capacity) {
                enlargearray(arr,size,3*capacity);
                capacity=capacity*3;          
        }
        stringstream  linestream(fileline);
        linestream>>n1>>n2>>weight;
        insertEdge(n1,n2,weight);
        bool exists=0;
        for (int i=0;i<size;i++){
            if(arr[i]==n1){
                exists=1;
                break;
            }
        }
        if (exists==0){
            arr[size]=n1;
            size++;
        }
        //το ιδιο για n2
        exists=0;
        for(int i=0;i<size;i++){
            if (arr[i]==n2){
                exists=1;
                break;
            }
        }
        if (exists==0){
            arr[size]=n2;
            size++;
        }
        
    }
    Verts=size;
    delete[] arr;
    file.close();
    }
    else{
        cerr<<"couldnt open file: "<<name<< endl;
        delete[] arr;
    }
    return;
}

/*
@brief Υπολογίζει την συντομότερη διαδρομή από source σε destination με τον αλγόριθμο Dijkstra
@param source η αρχική κορυφή
@param destination η τελική κορυφή
@return Επιστρέφει το συνολικό βάρος της διαδρομής ή -1 αν δεν υπάρχει
*/
int Graph::computeShortestPath(int source ,int destination){
    int *distance=new int[MAXelements];
    MINHEAP heap(Verts);
    bool *shortestpath=new bool[MAXelements];
    const long int upperlimit=LONG_MAX;
    //εφαρμοζουμε αλγοριθμο Dijkstra
    for (int i=0;i<MAXelements;++i){
        distance[i]=upperlimit;
        shortestpath[i]=false;
    }
    distance[source]=0;
    heap.insert(source);
    while(!heap.isempty()){
        int minv=heap.FINDMIN();
        heap.deletemin();
        shortestpath[minv]=true;
         
     for (Edge *temp=adjMatrix[minv];temp!=nullptr;temp=temp->next){
        int v=temp->destV;
        int weight=temp->weight;
        if (shortestpath[v]==false && distance[minv]!=upperlimit && distance[minv] + weight< distance[v]){
            distance[v]=distance[minv]+weight;
            heap.insert(v);
            int heapsize=heap.GETSIZE();
            heap.ensureheap(heapsize-1);
    
        }
     }   

    }
    int MinDistance=distance[destination];
    delete[] distance;
    delete[] shortestpath;
    if (MinDistance!=upperlimit)
    return MinDistance;
    else
    return -1;

}
/*
@brief Υπολογίζει πόσες συνδεδεμένες συνιστώσες έχει ο γράφος με χρήση DFS
@return Επιστρέφει τον αριθμό των συνιστωσών
*/
int Graph::findConnectedComponents(){
    int count=0;
    bool *visited=new bool[Verts];
    for (int i=0;i<Verts;i++)
        visited[i]=false;
    for (int i=0;i<Verts;i++){
        if(visited[i]==false){
            DFSalgo(i,visited);
            count ++;
        }
    }
    delete[] visited;
    return count;

}
/*
@brief Υπολογίζει το συνολικό βάρος του ελάχιστου συνδετικού δέντρου με τον αλγόριθμο Prim
@return Το βάρος του MST
*/
int Graph::computeSpanningTree() {
    bool* inMST = new bool[MAXelements];
    int* key = new int[MAXelements];
    int* parent = new int[MAXelements];
    
    for (int i = 0; i < MAXelements; ++i) {
        inMST[i] = false;
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    int start = -1;
    for (int i = 0; i < MAXelements; ++i) {
        if (hashtable.search(i)) {
            start = i;
            break;
        }
    }
    key[start] = 0;
    MINHEAP heap(MAXelements);
    heap.insert(start);

    int totalWeight = 0;

    while (!heap.isempty()) {
        int u = heap.FINDMIN();
        heap.deletemin();

        if (inMST[u]) continue;// skip εαν εχει μπει στον κομβο αυτο 
        inMST[u] = true;
        totalWeight += key[u];

        for (Edge* temp = adjMatrix[u]; temp != nullptr; temp = temp->next) {
            int v = temp->destV;
            int w = temp->weight;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                heap.insert(v);
            }
        }
    }

    delete[] inMST;
    delete[] key;
    delete[] parent;

    return totalWeight;
}

/*
@brief Εκτυπώνει τον γράφο 
@param output αρχείο εξόδου
*/
void Graph::printGraph(ofstream &output){
    for (int i=0;i<MAXelements;i++){
        if (hashtable.search(i)){
            output<<"Vertex "<<i<<"";
            Edge *temp=adjMatrix[i];
            while (temp!=nullptr){
                output <<"->[destination "<<temp->destV<<" ,weight "<< temp->weight <<"]";
                temp=temp->next;
            }
            output<< endl;
        }
    }
}

/*
@brief Εκτελεί αναδρομικό DFS από δοσμένο κόμβο
@param vert η αρχική κορυφή
@param visited πίνακας με τις ήδη κορυφές που εχουν επισκεφθεί
*/
void Graph::DFSalgo(int vert,bool *visited){
    visited[vert]=1;
    Edge *temp;
    for (Edge *temp=adjMatrix[vert];temp!=nullptr;temp=temp->next){
        int destination=temp->destV;
        if (visited[destination]==0){
            //αναδρομικη κληση
            DFSalgo(destination,visited);
        }
    }
}