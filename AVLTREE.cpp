#include "AVLTREE.h"
#include <string>
#include <fstream>
/*
@brief Κατασκευαστής της κλασης AVLtree
Αρχικοποιεί τη ρίζα του δένδρου ως nullptr
*/
AVLtree::AVLtree(){//αρχικοποιηση του avl tree
    root=nullptr;
}
/*
@brief Καταστροφέας της AVLtree
Καταστρέφει αναδρομικά μεσω αλλης συναρτησης όλους τους κόμβους του δένδρου
*/
AVLtree::~AVLtree(){//καταστροφη του avl tree
    destroyTree(root);
    root=nullptr;
}
/*
@brief Υπολογίζει το ύψος ενός κόμβου
@param n ο κόμβος 
@return το ύψος του κόμβου 
*/
int AVLtree::height(AVLNode*n){
    if (n!=nullptr)
        return n->height;
    else
        return 0;
}
/*
@brief Επιστρέφει το μέγιστο από δύο ακέραιους
@return ο μέγιστος από τους a και b
*/
int AVLtree::max(int a,int b){
    if (a>b)
        return a;
    else
        return b;
}
/*
@brief Υπολογίζει τον συντελεστή ισορροπίας ενός κόμβου
@param n ο κόμβος
@return η διαφορά ύψους μεταξύ αριστερού και δεξιού υποδένδρου
*/
int AVLtree::BalanceFactor(AVLNode *n){
    if (n!=nullptr)
        return height(n->left)-height(n->right);
    return 0;
}
/*
@brief Εκτελεί δεξιά περιστροφή στον κόμβο y
@param y η ρίζα του μη ισορροπημένου υποδένδρου
@return την νέα ρίζα του υποδένδρου
*/
AVLNode *AVLtree::rightRotate(AVLNode *y){
    AVLNode *L=y->left;
    AVLNode *LR=L->right;

    L->right=y;
    y->left=LR;
    
    y->height=max(height(y->left),height(y->right))+1;
    L->height=max(height(L->left),height(L->right))+1;

    return L;
}
/*
@brief Εκτελεί αριστερή περιστροφή στον κόμβο x
@param x η ρίζα του μη ισορροπημένου υποδένδρου
@return την νέα ρίζα του υποδένδρου
*/
AVLNode *AVLtree::leftRotate(AVLNode *x){
    AVLNode *R=x->right;
    AVLNode *RL=R->left;

    R->left=x;
    x->right=RL;

    x->height = max(height(x->left), height(x->right)) + 1;
    R->height = max(height(R->left), height(R->right)) + 1;

    return R;
}
/*
@brief Θέτει τη ρίζα του δένδρου
@param r ο νέος κόμβος ρίζας
*/

void AVLtree::setRoot(AVLNode *r){
    root=r;
}
/*
@brief Επιστρέφει τη ρίζα του δένδρου
@return την ρίζα του δένδρου
*/
AVLNode* AVLtree::getRoot(){
  return root;  
} 

/*
@brief ελάχιστος κόμβος σε ένα υποδένδρο
@param r η ρίζα του υποδένδρου
@return κόμβος με το ελάχιστο κλειδί
*/
AVLNode *AVLtree::minofsubtree(AVLNode *r){
    AVLNode *down=r;
    while(down && down->left){
        down=down->left;
    }
    return down;

}
/*
@brief Αναζητεί ένα στοιχείο στο AVL δέντρο
@param r η ρίζα του υποδένδρου
@param key το κλειδί που αναζητείται
@return μήνυμα εύρεσης ή μη εύρεσης του στοιχείου
*/
string AVLtree::search(AVLNode *r,int key){
    if (r==nullptr){
    return "DID NOT FIND KEY";
    }
    //Αν βρηκαμε το κλειδι
    if (r->key==key){
    return to_string (key);
    }
    //Αν το κλειδι ειναι μικροτερο συνεχιζει στο αριστερο υπονδεδρο
    if (key<r->key){
        return search(r->left,key);
    }
    //Αν το κλειδι ειναι μεγαλυτερο,συνεχιζει στο δεξι υποδενδρο
    return search(r->right,key);
}
/*
@brief Εισαγωγή στοιχείου στο AVL δέντρο
@param r η ρίζα του υποδένδρου
@param key το κλειδί που θα εισαχθεί
@return η νέα ρίζα μετά την εισαγωγή και τυχόν αναδιάρθρωση
*/
AVLNode *AVLtree::insert(AVLNode *r,int key){
    if (r==nullptr){
        return  new AVLNode(key);
    } 
    if (key<r->key){
        r->left=insert(r->left,key);
    }
    else if(key>r->key){
        r->right=insert(r->right,key);

    }
    else {
        return r;

    }
    r->height = 1 + max(height(r->left),height(r->right));
    int bf=BalanceFactor(r);//βρισκουμε ισορροπια κομβου
    if (bf>1 && key<r->left->key)
        return rightRotate(r);//left left rotation 
    if (bf<-1 &&key>r->right->key)
        return leftRotate(r);//right right rotation
    if (bf>1 && key>r->left->key){
        r->left=leftRotate(r->left);//left rotation
        return rightRotate(r);//right rotation
    }
    if (bf<-1 && key<r->right->key){
        r->right=rightRotate(r->right);//right rotation
        return leftRotate(r);//left
    }
    return r;
}
/*
@brief Δημιουργεί AVL δέντρο από έναν πίνακα ακεραίων
@param arr ο πίνακας με τα κλειδιά
@param size το μέγεθος του πίνακα
*/
void AVLtree::buildAVLTree(int *arr,int size){
    AVLNode *r = nullptr;
    for (int i = 0; i < size; ++i) {
        r = insert(r, arr[i]);
    }
    setRoot(r);
}
/*
@brief Εκτελεί ενδοδιάταξη (in-order traversal) και την παρουσιαζει σε αρχείο
@param root η ρίζα του υποδένδρου
@param output το αρχείο εξόδου
*/
void AVLtree::inOrderTraversal(AVLNode *root,ofstream &output){
    if (root==nullptr){
        return;
    }
    inOrderTraversal(root->left,output);
    output<<root->key<<" ";
    inOrderTraversal(root->right,output);
}
/*
@brief Καταστρέφει αναδρομικά το δέντρο ξεκινώντας από τον κόμβο node
@param node ο κόμβος από τον οποίο ξεκινά η διαγραφή
*/
void AVLtree::destroyTree(AVLNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
/*
@brief Διαγράφει έναν κόμβο από το AVL δέντρο και εξασφαλίζει την ισορροπία του
@param r η ρίζα του υποδένδρου
@param key το κλειδί προς διαγραφή
@return η νέα ρίζα του υποδένδρου
*/
AVLNode* AVLtree::deleteNode(AVLNode* r, int key) {
    if (r == nullptr)
        return r;

    // Βασική διαγραφή BST
    if (key < r->key)
        r->left = deleteNode(r->left, key);
    else if (key > r->key)
        r->right = deleteNode(r->right, key);
    else {
     
        if (r->left == nullptr || r->right == nullptr) {
            AVLNode* temp = r->left ? r->left : r->right;

            if (temp == nullptr) { 
                temp = r;
                r = nullptr;
            } else {
                *r = *temp; 
            }

            delete temp;
        } else {
            AVLNode* temp = minofsubtree(r->right);
            r->key = temp->key;
            r->right = deleteNode(r->right, temp->key);
        }
    }

  
    if (r == nullptr)
        return r;

    // Ενημέρωση ύψους
    r->height = 1 + max(height(r->left), height(r->right));

   
    int bf = BalanceFactor(r);
    // Left Left
    if (bf > 1 && BalanceFactor(r->left) >= 0)
        return rightRotate(r);
    // Left Right
    if (bf > 1 && BalanceFactor(r->left) < 0) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    // Right Right
    if (bf < -1 && BalanceFactor(r->right) <= 0)
        return leftRotate(r);
    // Right Left
    if (bf < -1 && BalanceFactor(r->right) > 0) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}
/*
@brief Υπολογίζει το πλήθος κόμβων του AVL δένδρου
@param node ο κόμβος από τον οποίο ξεκινά η μέτρηση
@return το μέγεθος του υποδένδρου
*/
int AVLtree::getSize(AVLNode* node) {
    if (node == nullptr) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}


