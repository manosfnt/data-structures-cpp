#include "HASHTABLE.h"
#include "List.h"
#include <iostream>
using namespace std;
/*
@brief Κατασκευαστής της HashTable
@param HashGroups το αρχικό μέγεθος του πίνακα κατακερματισμού (αριθμός group aka buvkets)
*/
HashTable::HashTable(int HashGroups) {

    this->HashGroups=HashGroups;
    currentHashGroups=0;
    htable=new List[HashGroups];
}

//@brief Καταστροφέας της HashTable
HashTable::~HashTable(){
    delete[] htable;
}
/*
@brief Υπολογίζει Load Factor του πίνακα
@return  Load Factorr ως δεκαδικός αριθμός
*/
const float HashTable::LoadFactor(){
    return currentHashGroups/(float)HashGroups;
}
/*
@brief Ανακατασκευάζει τον πίνακα κατακερματισμού όταν ξεπεραστεί ο Load factor και 
αυξάνει το μέγεθος του πίνακα και ξαναεισάγει τα δεδομένα σε νέο πίνακα
*/
void HashTable::resize(){
    int previous=HashGroups;//προσθετουμε θεσεις στο hashtable
    HashGroups=HashGroups*mult;
    int pointer;
    List *NewTable= new List[HashGroups];
    //αντιγραφη στοιχειων στο καινουργιο hashtable
    for (int i=0; i<previous ;i++){
        Node *temp=htable[i].getHeader();
        while (temp != nullptr){
            pointer=hashingfuction(temp->key);
            NewTable[pointer].insert(temp->key);
            temp=temp->next;
        }
    }
    delete[] htable;
    htable=NewTable;
    }

/*
@brief συνάρτηση κατακερματισμού
@param key το κλειδί 
@return ο δείκτης του πίνακα όπου ανήκει το κλειδί
*/
int HashTable::hashingfuction(int key){
    return key % HashGroups;

}
/*
@brief Επιστρέφει το τρέχον πλήθος κάδων του πίνακα κατακερματισμού
@return αριθμός buckets
*/
int HashTable::getHashGroups(){
    return HashGroups;
}
/*
@brief Εισαγωγή στοιχείου στην δομή HashTable
@param key το κλειδί προς εισαγωγή
*/
void HashTable::insert(int key){
    int i = hashingfuction(key);
    
   
    if (htable[i].isEmpty()) {
        currentHashGroups++;
        if (LoadFactor() > LFlimit) {
            resize();
        }
    }
    
    htable[i].insert(key);
}
/*
@brief Έλεγχος αν το στοιχείο υπάρχει στην δομή HashTable
@param key το στοιχείο προς αναζήτηση
@return true αν βρέθηκε, false αλλιώς
*/
bool HashTable::search(int key){
    int i = hashingfuction(key);
    
    return htable[i].search(key);
}
/*
@brief Δημιουργεί HashTable από έναν πίνακα ακεραίων
@param A ο πίνακας με τα δεδομένα
@param n το πλήθος των στοιχείων του πίνακα
*/
void HashTable::BuildHashTable(int *A,int n){
    int i=0;
    for(int i=0;i<n ;++i){
        insert(A[i]);
    }
}
/*
@brief Εκτυπώνει το περιεχόμενο της δομής HashTable σε αρχείο
@param output το αρχείο εξόδου
*/
void HashTable::printHashTable(ofstream &output){
    for (int i=0;i<HashGroups;i++){
        output<<"Bucket"<< i << ":";
        
        htable[i].printlist(output);

        output<<endl;
        }
}





