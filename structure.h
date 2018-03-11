#include <stdio.h>

typedef struct Node NODE;

typedef struct Key{
    int key;
    int n;
} KEY;

struct Node{
    KEY* key;
    NODE* parent;
    NODE* left;
    NODE* right;
    int inList;
    int isLeaf;
};

typedef struct Tree{
    NODE* root;
} TREE;

typedef struct Iterator{
    TREE* t;
    NODE* current;
    NODE* last;
} I;

void freeNode(NODE* n);
NODE* treeInsert(TREE* t, NODE* z);
KEY* createKey(int k);
NODE* createNode();

TREE* createTree(){
    TREE *t=malloc(sizeof(TREE));
    t->root=createNode();
    t->root->parent=NULL;
    return t;
}

NODE* createNode(){
    NODE* n=malloc(sizeof(NODE));
    n->inList=0;
    n->isLeaf=1;
    n->left=NULL;
    n->right=NULL;
    return n;
}

KEY* createKey(int k){
    KEY* key=malloc(sizeof(KEY));
    key->n=1;
    key->key=k;
    return key;
}

NODE* addNode(TREE* t, int k){
    NODE* n=createNode();
    KEY* key =createKey(k);
    n->key=key;
    return treeInsert(t, n);
}

NODE* treeInsert(TREE* t, NODE* z){
    NODE* x=t->root;
    while(!x->isLeaf){
        if(x->left) {
            if (z->key->key < x->key->key){
                x = x->left;
                continue;
            }
        }
        else {
            if(z->key->key<x->key->key)
                break;
        }
        if(x->right) {
            if (z->key->key > x->key->key){
                x = x->right;
                continue;
            }
        }
        else {
            if(z->key->key>x->key->key)
                break;
        }
        break; //the cell with key exists and we found it
    }
    if(!x->inList){
        t->root=z;
        z->inList=1;
        freeNode(x);
    }
    else{
        x->isLeaf=0;
        z->inList=1;
        z->parent=x;
        if(z->key->key<x->key->key)
            x->left=z;
        if(z->key->key==x->key->key){
            x->key->n=x->key->n+1;
            freeNode(z);
            return x;
        }
        if(z->key->key>x->key->key)
            x->right=z;
    }
    return z;
}

void freeNode(NODE* n){
    free(n->key);
    free(n);
}



I* createIterator(TREE* t){

}

NODE* next(I* i){

}