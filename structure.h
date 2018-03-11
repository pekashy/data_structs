#include <stdio.h>

typedef struct Node NODE;

typedef struct Key{
    int key;
    int n;
} KEY;

struct Node{
    KEY* key;
    NODE* left;
    NODE* right;
    int inList; //must be 1 or isNil
};

typedef struct Tree{
    NODE* root;
} TREE;

void freeNode(NODE* n);
NODE* treeInsert(TREE* t, NODE* z);
KEY* createKey(int k);
NODE* createNode();

TREE* createTree(){
    TREE *t=malloc(sizeof(TREE));
    t->root=createNode();
    t->root->inList=1;
    return t;
}

NODE* createNode(){
    NODE* n=malloc(sizeof(NODE));
    n->inList=0;
    return n;
}


NODE* addNode(TREE* t, int k){
    NODE* n=createNode();
    KEY* key =createKey(k);
    n->key=key;
    return treeInsert(t, n);
}

NODE* treeInsert(TREE* t, NODE* z){
    NODE* y=createNode();
    NODE* x=t->root;
    while(x->inList){
        y=x;
        if(z->key->key<x->key->key)
            x=x->left;
        if(z->key->key==x->key->key){
            x->key->n=x->key->n+1;
            freeNode(z);
            return x;
        }
        if(z->key->key>x->key->key)
            x=x->right;
    }
    //p[z]=y ???
    if(!y->inList){
        t->root=z;
        freeNode(y);
    }
    else{
        if(z->key->key<y->key->key)
            y->left=z;
        if(z->key->key==x->key->key){
            x->key->n=x->key->n+1;
            freeNode(z);
            return x;
        }
        if(z->key->key>x->key->key)
            y->right=z;
    }
    return z;
}

void freeNode(NODE* n){
    free(n->key);
    free(n);
}

KEY* createKey(int k){
    KEY* key=malloc(sizeof(KEY));
    key->n=1;
    key->key=k;
    return key;
}
