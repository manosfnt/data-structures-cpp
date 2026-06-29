#include "MINHEAP.h"
#include "MAXHEAP.h"
#include "AVLTREE.h"
#include "HASHTABLE.h"
#include "GRAPH.h"
#include "FUCTIONS.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <thread>
using namespace std;

/*
@brief Κύρια συνάρτηση που διαβάζει εντολές από αρχείο και εκτελεί πράξεις πάνω στις δομές 
@return 0 σε επιτυχή εκτέλεση, -1 σε σφάλμα ανοίγματος αρχείων
*/
int main(){
   
    string comm,comm2,comm3;
    ifstream mf("commands.txt");//αρχείο με εντολές εισόδου
    ofstream output("output.txt");//αρχείο εξόδου
    int size1, size2, size3;

    
    if (!mf.is_open() || !output.is_open()){
        cerr<<"Unable to open file"<<endl;
        return -1;
    }
    ////////////////////////////////////////////////
        //αρχικοποίηση δομών
        MINHEAP minheap(150);
        MAXHEAP maxheap(150);
        AVLtree avltree;
        Graph graph;
        HashTable  hashtable(10);
        string line;
        
         output << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
         while(getline(mf,line)){
            stringstream s(line);
            s>>comm>>comm2>>comm3;
            int n1,n2,weight;
            //μετρηση χρόνου
            auto startingtime= std::chrono::high_resolution_clock::now();

            /*
            @brief Χτίσιμο δομών δεδομένων από αρχείο
            */
            if (comm=="BUILD"){
                s>>comm3;
                
                
                if (comm2=="MINHEAP"){//build minheap
                        int min;
                        int* minarr=integersfromfile(comm3,min);
                        minheap.buildheap(minarr,min);
                        output<<"Min heap constructed: "<<endl;
                        minheap.printheap(output);
                        delete[] minarr;
                }else if (comm2=="MAXHEAP"){//build maxheap
                        int max;
                        output <<"Max heap constructed: "<<endl;
                        int *maxarr=integersfromfile(comm3,max);
                        maxheap.buildheap(maxarr,max);
                        maxheap.printheap(output);
                        delete[] maxarr;
                }else if (comm2=="AVLTREE"){
                        int avlsize;
                        int *avlarr=integersfromfile(comm3,avlsize);
                        AVLNode* root=avltree.getRoot();
                        for (int i=0;i<avlsize ;i++){
                            root=avltree.insert(root,avlarr[i]);
                        }
                        avltree.setRoot(root);
                        output << "AVL tree constructed: "<<endl;
                        avltree.inOrderTraversal(avltree.getRoot(),output);
                        output<<endl;
                        delete[] avlarr;

                }else if (comm2=="GRAPH"){
                    graph.BuildGraph(comm3);
                    output<<"Graph constructed: "<<endl;
                    graph.printGraph(output);
                }else if (comm2=="HASHTABLE"){//build hashtable
                    int hashsize;
                    int *hasharr=integersfromfile(comm3,hashsize);
                    output<<"Hash array constructed: "<<endl;
                    hashtable.BuildHashTable(hasharr,hashsize);
                    hashtable.printHashTable(output);
                    
                }   
            }
            /*
            @brief Εμφάνιση μεγέθους δομής
            */
            else if (comm=="GETSIZE"){
                if (comm2=="MINHEAP"){//minheap size
                    output<<"Current Min heap size is: "<<minheap.GETSIZE()<<endl;
                }else if (comm2=="MAXHEAP"){//maxheap size
                    output<<"Current Max heap size is: "<<maxheap.GETSIZE()<<endl;
                }else if (comm2=="AVLTREE"){
                    output << "Current AVL tree size is: "<< avltree.getSize(avltree.getRoot())<< endl;
                }else if (comm2=="GRAPH"){
                    int edges=graph.getEdges();
                    int verts=graph.getVerts();
                    output<<"Current graph size is: "<<verts<<"[vertices]-"<<edges<<"[edges]"<<endl;
                }else if (comm2=="HASHTABLE"){
                    output<<"Current hashtable size is: "<< hashtable.getHashGroups()<<endl;
                }
            }
             /*
            @brief Εύρεση ελάχιστου ή μέγιστου στοιχείου
            */
            else if (comm=="FINDMIN"){
                if (comm2=="MINHEAP"){//minheap min
                    output<<"The Minimum element of heap is: "<<minheap.FINDMIN()<<endl;
                }
                else if (comm2=="AVLTREE"){
                    AVLNode* minNode = avltree.minofsubtree(avltree.getRoot());
                    output << "The Minimum element of AVL tree is: " << minNode->key << endl;
                }
            }
            else if (comm=="FINDMAX"){
                if (comm2=="MAXHEAP"){
                    output<<"The maximum element of heap is: "<<maxheap.FINDMAX()<<endl;
                }
            }
            /*
            @brief Αναζήτηση στοιχείου σε AVL ή HashTable
            */
           else if (comm=="SEARCH"){
                if (comm2=="AVLTREE"){
                    n1=stoi(comm3);
                    string result=avltree.search(avltree.getRoot(),n1);
                    if (result=="DID NOT FIND KEY")
                         output << "Element " << n1 << " wasn't found in AVL tree" << endl;
                    else
                         output << "Element " << n1 << " was found in AVL tree" << endl;
                }
                else if (comm2=="HASHTABLE"){
                    n1=stoi(comm3);
                    if (hashtable.search(n1)){
                        output<<"Element "<<n1<<" was found in hashtable"<<endl;
                    }
                    else{
                    output<<"Element "<<n1<<"wasn't found in hashtable"<<endl;
                    }
                }
           }
            /*
            @brief Υπολογισμός shortest path με Dijkstra
            */
           else if (comm=="COMPUTESHORTESTPATH"){
                if (comm2=="GRAPH"){
                    s>>n1>>n2;
                    output<<"Shortest path"<<"["<<n1<<"<->"<<n2<<"]:"<<graph.computeShortestPath(n1,n2)<<endl;

                }
           }
            /*
            @brief Υπολογισμός MST
            */
            else if (comm=="COMPUTESPANNINGTREE"){
                if (comm2=="GRAPH"){
                    output<<"Total weight of minimum spanning tree: "<<graph.computeSpanningTree()<<endl;
                }
            
            }
            /*
            @brief Υπολογισμός connected components
            */
            else if (comm=="FINDCONNECTEDCOMPONENTS"){
                if (comm2=="GRAPH"){
                    output<<"Number of connected components: "<<graph.findConnectedComponents()<<endl;
                }
            }

            /*
            @brief Εισαγωγή νέου στοιχείου σε δομή
            */
            else if (comm=="INSERT"){
                if (comm2=="MINHEAP"){
                    n1=stoi(comm3);
                    minheap.insert(n1);
                    output<<"Inserting "<<n1<<" in the MinHeap:"<<endl;
                    minheap.printheap(output);
                }
                else if (comm2=="MAXHEAP"){
                     n1=stoi(comm3);
                    maxheap.insert(n1);
                    output<<"Inserting "<<n1<<" in the Minheap:"<<endl;
                    maxheap.printheap(output);
                }
                else if (comm2=="AVLTREE"){
                    n1=stoi(comm3);
                    AVLNode* root=avltree.getRoot();
                    root=avltree.insert(root,n1);
                    avltree.setRoot(root);
                    output << "Inserting " << n1 << " in the AVL tree:" << endl;
                    avltree.inOrderTraversal(avltree.getRoot(), output);
                    output << endl;
                }
                else if (comm2=="HASHTABLE"){
                     n1=stoi(comm3);
                    hashtable.insert(n1);
                    output<<"Inserting "<<n1<<" in the hashtable: "<<endl;
                    hashtable.printHashTable(output);
                }
                else if (comm2=="GRAPH"){
                    n1=stoi(comm3);
                    s>>n2>>weight;
                    graph.insertEdge(n1,n2,weight);
                    output<<"Inserting["<<n1<<"."<<n2<<"."<<weight<<"]"<<endl;
                    graph.printGraph(output);
                    
                }
            }
            /*
            @brief Διαγραφή ελάχιστου/μέγιστου ή συγκεκριμένου κόμβου
            */
            else if (comm=="DELETEMIN"){
                if (comm2=="MINHEAP"){//delete min
                    minheap.deletemin();
                    output<<"Min heap after removing the minimum element:"<<endl;
                    minheap.printheap(output);
                }
            }
            else if (comm=="DELETEMAX"){
                if (comm2=="MAXHEAP"){
                    maxheap.deletemax();
                    output<<"Max heap after removing the maximum element:"<<endl;
                    maxheap.printheap(output);
                }
            }
            else if (comm=="DELETE"){
                if (comm2=="AVLTREE"){
                    n1=stoi(comm3);
                    AVLNode* root=avltree.getRoot();
                    root=avltree.deleteNode(root,n1);
                    avltree.setRoot(root);
                    output << "AVL tree after deleting " << n1 << ":" << endl;
                    avltree.inOrderTraversal(avltree.getRoot(), output);
                    output << endl;
                }
                else if (comm2=="GRAPH"){
                    s>>n1>>n2;
                    graph.deleteEdge(n1,n2);
                    output<<"Graph after deleting ["<<n1<<"."<<n2<<"]"<<endl;
                    graph.printGraph(output);
                }
            }
             //υπολογισμος duration
             auto stopingtime = std::chrono::high_resolution_clock::now();
             unsigned long int  time= (std::chrono::duration_cast<std::chrono::nanoseconds>(stopingtime-startingtime)).count();
             
             if (time==0){
             output<<"The duration is too small to count"<<endl;   
             }
             output<<"Duration: "<<time<<" nanoseconds!"<<endl;
             output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

                
            }
        
 mf.close();
 output.close();
return 0;
 }

//βοηθητικη
/*
@brief Διαβάζει ακέραιους από αρχείο και επιστρέφει πίνακα
@param filename όνομα αρχείου
@param size [output] το μέγεθος του πίνακα
@return pointer στον πίνακα με τους αριθμούς
*/
inline int* integersfromfile(const std::string& filename, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }

    int capacity = 10;
    int* arr = new int[capacity];
    int count = 0;
    std::string line;

    while (std::getline(file, line)) {
        if (count == capacity) {
            enlargearray(arr, capacity, capacity * 2);
        }
        arr[count] = std::stoi(line);
        count++;
    }

    file.close();

    if (count < capacity) {
        enlargearray(arr, capacity, count);
    }

    size = count;
    return arr;
}


        
        

        
    
     
        
        
        
        
        
        
        
    
 
