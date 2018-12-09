#include "arvoreB.h"

using namespace std;
int Contador = 0;
// Constructor for BTreeNode class 
BTreeNode::BTreeNode(int t1, bool leaf1) 
{ 
    // Copy the given minimum degree and leaf property 
    t = t1; 
    leaf = leaf1; 
  
    // Allocate memory for maximum number of possible keys 
    // and child pointers 
    keys = new string[2*t-1]; 
    C = new BTreeNode *[2*t]; 
  
    // Initialize the number of keys as 0 
    n = 0; 
} 
  
// Function to traverse all nodes in a subtree rooted with this node 
void BTreeNode::traverse() 
{ 
    // There are n keys and n+1 children, travers through n keys 
    // and first n children 
    int i; 
    for (i = 0; i < n; i++) 
    { 
        // If this is not leaf, then before printing key[i], 
        // traverse the subtree rooted with child C[i]. 
        if (leaf == false) 
            C[i]->traverse(); 
        cout << " " << keys[i]; 
    } 
  
    // Print the subtree rooted with last child 
    if (leaf == false) 
        C[i]->traverse(); 
} 
  
// Function to search key k in subtree rooted with this node 
BTreeNode *BTreeNode::search(string k, int* cont) 
{ 
    (*cont)++;
    // Find the first key greater than or equal to k 
    int i = 0; 
    while (i < n && keys[i].substr(0, 8).compare(k) < 0) 
        i++; 
  
    // If the found key is equal to k, return this node 
    //keys[i]
    if (keys[i].find(k) != string::npos) 
        return this; 
  
    // If key is not found here and this is a leaf node 
    if (leaf == true) 
        return NULL; 
  
    // Go to the appropriate child 
    return C[i]->search(k, cont); 
} 
  
// The main function that inserts a new key in this B-Tree 
void BTree::insert(string k) 
{ 
    // If tree is empty 
    if (root == NULL) 
    { 
        // Allocate memory for root 
        root = new BTreeNode(t, true); 
        root->pagina = Contador;
        Contador++;
        root->keys[0] = k;  // Insert key 
        root->n = 1;  // Update number of keys in root 
    } 
    else // If tree is not empty 
    { 
        // If root is full, then tree grows in height 
        if (root->n == 2*t-1) 
        { 
            // Allocate memory for new root 
            BTreeNode *s = new BTreeNode(t, false); 
            s->pagina = Contador;
            Contador++;
            // Make old root as child of new root 
            s->C[0] = root; 
  
            // Split the old root and move 1 key to the new root 
            s->splitChild(0, root); 
  
            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0; 
            if (s->keys[0].substr(0, 8).compare(k.substr(0, 8)) < 0) 
                i++; 
            s->C[i]->insertNonFull(k); 
  
            // Change root 
            root = s; 
        } 
        else  // If root is not full, call insertNonFull for root 
            root->insertNonFull(k); 
    } 
} 
  
// A utility function to insert a new key in this node 
// The assumption is, the node must be non-full when this 
// function is called 
void BTreeNode::insertNonFull(string k) 
{ 
    // Initialize index as index of rightmost element 
    int i = n-1; 
  
    // If this is a leaf node 
    if (leaf == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && keys[i].substr(0, 8).compare(k.substr(0, 8)) > 0) 
        { 
            keys[i+1] = keys[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        keys[i+1] = k; 
        n = n+1; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && keys[i] > k) 
            i--; 
  
        // See if the found child is full 
        if (C[i+1]->n == 2*t-1) 
        { 
            // If the child is full, then split it 
            splitChild(i+1, C[i+1]); 
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (keys[i+1].substr(0, 8).compare(k.substr(0, 8)) < 0) 
                i++; 
        } 
        C[i+1]->insertNonFull(k); 
    } 
} 
  
// A utility function to split the child y of this node 
// Note that y must be full when this function is called 
void BTreeNode::splitChild(int i, BTreeNode *y) 
{ 
    // Create a new node which is going to store (t-1) keys 
    // of y 
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->pagina = Contador;
    Contador++;
    z->n = t - 1; 
  
    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < t-1; j++) 
        z->keys[j] = y->keys[j+t]; 
  
    // Copy the last t children of y to z 
    if (y->leaf == false) 
    { 
        for (int j = 0; j < t; j++) 
            z->C[j] = y->C[j+t]; 
    } 
  
    // Reduce the number of keys in y 
    y->n = t - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = n; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    // Link the new child to this node 
    C[i+1] = z; 
  
    // A key of y will move to this node. Find location of 
    // new key and move all greater keys one space ahead 
    for (int j = n-1; j >= i; j--) 
        keys[j+1] = keys[j]; 
  
    // Copy the middle key of y to this node 
    keys[i] = y->keys[t-1]; 
  
    // Increment count of keys in this node 
    n = n + 1; 
} 


void make_Btree(const char* filename, BTree* t) {
    fstream fp;
    fp.open(filename);
    int cont = 0, index = 0;
    char c;
    char chave[10];

    string line;        

    while (getline(fp, line)) {
        string nome, num, chave;
        
        //chave += "|";
        nome = upper_case(line.substr(0, 3));
        num = line.substr(41, 5);
        chave = nome + num;
        chave += "|";
        chave += to_string(cont);
        if(chave.size() < 4) {
            if(chave.size() < 3) {
                if(chave.size() < 2) {
                    chave.insert(0, "0");
                }
                chave.insert(0, "0");
            }
            chave.insert(0, "0");
        }
        t->insert(chave);
        cout << chave << endl;
        cont++;
    } 
    fp.close();
}

string upper_case(string nome) {
    for (int i = 0; i < 3; i++) {
        nome[i] = toupper(nome[i]);
    }
    return nome;
}

void createArqu(BTree* t){
    FILE* fp;
    fp = fopen("BTree.txt", "w");
    fprintf(fp, "raiz = %d\n", t->root->pagina);

    printPag(t->root, fp);
    fclose(fp);
}

void printPag(BTreeNode* node, FILE* fp){
    int val = node->t;
    for(int i = 0;i < node->n + 1;i++){
        if(!(node->leaf)) {            
            printPag(node->C[i], fp);
        }
    }
    fprintf(fp,"pagina %d  ", node->pagina);
    for(int i = 0;i < (val*2)-1;i++) {
        if(node->leaf){
            fprintf(fp, "||#");
        } else if(node->C[i] != NULL){
            fprintf(fp, "||%d", node->C[i]->pagina);
        } else {
            fprintf(fp, "||#");
        }
        if(i >= node->n) {
            fprintf(fp, "||***********");
        } else {
            fprintf(fp, "||%s", node->keys[i].c_str());
        }
    }
    if(node->C[node->n+1] == NULL){
        fprintf(fp, "||#");
    } else {
        fprintf(fp, "||%d", node->C[(val * 2)-1]->pagina);
    }
    fprintf(fp, "\n");
}

int retornaPonteiro(BTreeNode* node, const char* item){
    int i = 0;
    string sItem = item;
    while(1) {
        if(node->keys[i].substr(0, 8).compare(sItem) == 0) {
            break;
        }
        i++;
    }
    sItem = node->keys[i].substr(9, 500);
    return stoi(sItem);
}

void recupera_reg(const char* filename, int ponteiro) {
    ifstream fp;
    string registro;
    fp.open(filename);
    fp.seekg(ponteiro*REG_SIZE);
    getline(fp, registro);
    cout << registro << endl;
    fp.close();
}

// Driver program to test above functions 
int main() 
{ 
    BTree t(3);
    make_Btree("../lista.txt", &t);
     // A B-Tree with minium degree 3 
    /*t.insert("9999|12345678"); 
    t.insert("6666|56634546"); 
    t.insert("3333|65463456"); 
    t.insert("2222|76834522"); 
    t.insert("4444|64564367"); 
    t.insert("8888|25454647"); 
    t.insert("7777|56436436"); 
    t.insert("5555|57682235"); 
  */
    cout << "Traversal of the constucted tree is "; 
    t.traverse(); 
  
    int teste;
    //teste = new int;
    teste = 0;
    string k = "CAR62364";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    int aux = retornaPonteiro(t.search(k, &teste), k.c_str());
    printf("\nponteiro = %d\n", aux);
    recupera_reg("../lista.txt", aux);
    teste = 0;
    k = "SAM76667";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "DIE29981";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "THI33977";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "AND71929";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "MIG12997";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "PAU55191";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "IGO22998";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "BER81293";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "WIL44654";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "NOR82344";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "GIU87658";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "UBI71831";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "RIC36352";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "KEI86567";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "ENI78651";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "HAR35522";  
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "OLI66441";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "LEO24312";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "JUL31272";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "YAS24262";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "QUI56776";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "ZEL28583";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "FER48436";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "XAV98776";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    k = "VAN27667";
    (t.search(k, &teste) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
    printf("\nNumero de seeks: %d\n", teste);
    teste = 0;
    createArqu(&t);

    printf("\n%d\n", Contador);
    //(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 
  
    return 0; 
} 
