#include "List.h"
#include <iostream>
using namespace std;
/*
@brief Κατασκευαστής της κλάσης List
Αρχικοποιεί την επικεφαλίδα της λίστας ως nullptr (κενή λίστα)
*/
List::List():header(nullptr){}
/*
@brief Καταστροφέας της λίστας
Απελευθερώνει τη μνήμη των κόμβων της λίστας
*/
List::~List(){
    Node *current=header;
    while (current!=nullptr){
        Node *next =current->next;
        delete current;
        current=next;
    }
}
/*
@brief Επιστρέφει τον δείκτη στην αρχή της λίστας
@return δείκτης προς τον πρώτο κόμβο (ή nullptr αν είναι κενή)
*/
Node* List::getHeader(){
    return header;
}
/*
@brief Εισάγει νέο στοιχείο στην αρχή της λίστας
@param key το κλειδί του νέου στοιχείου
*/
void List::insert(int key){
    Node *newNode = new Node(key);
    newNode ->next =header;
    header=newNode;

}
/*
@brief Αναζητά ένα στοιχείο με βάση το κλειδί του
@param key το στοιχείο προς αναζήτηση
@return true αν το στοιχείο βρεθεί, false αλλιώς
*/
bool List::search(int key){
    Node *temp=header;
    while(temp!=nullptr){
        if(temp->key==key){
            return 1;
        }
        temp=temp->next;
    
    }
    return 0;

}
/*
@brief Εκτυπώνει όλα τα στοιχεία της λίστας σε αρχείο
@param output το αρχείο εξόδου όπου θα γραφούν τα στοιχεία
*/
void List::printlist(ofstream &output){
    Node *temp=header;
    while ( temp!=nullptr){
        output<<temp->key<<", ";
        temp=temp->next;
    }

}
/*
@brief Ελέγχει αν η λίστα είναι κενή
@return true αν είναι κενή, false αλλιώς
*/
bool List::isEmpty(){
    return getHeader()==nullptr;
}