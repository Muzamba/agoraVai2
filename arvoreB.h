// C++ program for B-Tree insertion 
#include<iostream> 
#include<string>
#include <ctype.h>
#include <fstream>
using namespace std; 

#define REG_SIZE 54
  
    
// A BTree node 
class BTreeNode 
{ 
public:
    string *keys;  // An array of keys 
    int t;      // Minimum degree (defines the range for number of keys) 
    BTreeNode **C; // An array of child pointers 
    int n;     // Current number of keys 
    bool leaf; // Is true when node is leaf. Otherwise false  
    int pagina;
    BTreeNode(int _t, bool _leaf);   // Constructor 
  
    // A utility function to insert a new key in the subtree rooted with 
    // this node. The assumption is, the node must be non-full when this 
    // function is called 
    void insertNonFull(string k); 
  
    // A utility function to split the child y of this node. i is index of y in 
    // child array C[].  The Child y must be full when this function is called 
    void splitChild(int i, BTreeNode *y); 
  
    // A function to traverse all nodes in a subtree rooted with this node 
    void traverse(); 
  
    // A function to search a key in subtree rooted with this node. 
    BTreeNode *search(string k, int* cont);   // returns NULL if k is not present. 
  
    // A function that returns the index of the first key that is greater 
    // or equal to k 
    int findKey(string k);

    // A wrapper function to remove the key k in subtree rooted with 
    // this node. 
    void remove(string k);

    // A function to remove the key present in idx-th position in 
    // this node which is a leaf 
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in 
    // this node which is a non-leaf node 
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key- where the key 
    // is present in the idx-th position in the node 
    string getPred(int idx);

    // A function to get the successor of the key- where the key 
    // is present in the idx-th position in the node 
    string getSucc(int idx);

    // A function to fill up the child node present in the idx-th 
    // position in the C[] array if that child has less than t-1 keys 
    void fill(int idx);

    // A function to borrow a key from the C[idx-1]-th node and place 
    // it in C[idx]th node 
    void borrowFromPrev(int idx);

    // A function to borrow a key from the C[idx+1]-th node and place it 
    // in C[idx]th node 
    void borrowFromNext(int idx);

    // A function to merge idx-th child of the node with (idx+1)th child of 
    // the node 
    void merge(int idx);

// Make BTree friend of this so that we can access private members of this 
// class in BTree functions 
friend class BTree; 
}; 
  
// A BTree 
class BTree 
{ 
    
    int t;  // Minimum degree 
public: 
    BTreeNode *root; // Pointer to root node 
    // Constructor (Initializes tree as empty) 
    BTree(int _t) 
    {  root = NULL;  t = _t; } 
  
    // function to traverse the tree 
    void traverse() 
    {  if (root != NULL) root->traverse(); } 
  
    // function to search a key in this tree 
    BTreeNode* search(string k, int* cont) 
    {  return (root == NULL)? NULL : root->search(k, cont); } 
  
    // The main function that inserts a new key in this B-Tree 
    void insert(string k);

    // The main function that removes a new key in thie B-Tree 
    void remove(string k); 
}; 

string upper_case(string nome);
void make_Btree(const char* filename, BTree *t);
void printPag(BTreeNode* node, FILE* fp);
void createArqu(BTree* t);
int retornaPonteiro(BTreeNode* node, const char* item);
void recupera_reg(const char* filename, int ponteiro);
void include_reg(const char* filename, BTree* t);
