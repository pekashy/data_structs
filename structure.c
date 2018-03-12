#include "structure.h"

void freeNode(NODE* n){
    free(n->key);
    free(n);
}

NODE* getNode(TREE* t, int key){
    NODE* n=t->root;
    while(n->key->key!=key){
        if(n->key->key > key) {
            if(n->left){
                n = n->left;
            }
            else{
                return NULL;
            }
        }
        else {
            if(n->right){
                n = n->right;
            }
            else{
                return NULL;
            }
        }
    }
    return n;
}

NODE* treeMin(NODE* r){
    NODE* n=r;
    while(n->left)
        n=n->left;
    return n;
}

NODE* treeMax(NODE* r){
    NODE* n=r;
    while(n->right)
        n=n->right;
    return n;
}

NODE* createNode(){
    NODE* n=malloc(sizeof(NODE));
    n->inList=0;
    n->isLeaf=1;
    n->left=NULL;
    n->right=NULL;
    n->key=NULL;
    n->parent=NULL;
    return n;
}

TREE* createTree(){
    TREE *t=malloc(sizeof(TREE));
    t->root=createNode();
    t->root->parent=NULL;
    return t;
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
            if(z->key->key < x->key->key){
                break;
            }
        }
        if(x->right) {
            if (z->key->key > x->key->key){
                x = x->right;
                continue;
            }
        }
        else {
            if(z->key->key > x->key->key){
                break;
            }
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
        if(z->key->key < x->key->key)
            x->left=z;
        if(z->key->key == x->key->key){
            x->key->n=x->key->n+1;
            freeNode(z);
            return x;
        }
        if(z->key->key>x->key->key)
            x->right=z;
    }
    return z;
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

NODE* nextElement(NODE* x){
    if(x->right)
        return treeMin(x->right);
    NODE* y=x->parent;
    while(y && y->right && x==y->right){
        x=y;
        y=y->parent;
    }
    return y;
}

void next(I* i){
    i->current=(nextElement(i->current));
    if(!i->current) i->isLast=1;
}

I* createIterator(TREE* t){
    I* i=malloc(sizeof(I));
    i->t=t;
    i->current=treeMin(t->root);
    i->next=&next;
    i->isLast=0;
    return i;
}

void deleteNode(TREE* t, NODE* z){
    NODE *x, *y;
    if(!z->left || !z->right)
        y=z;
    else y=nextElement(z);
    if(y->left)
        x=y->left;
    else
        x=y->right;
    if(x)
        x->parent=y->parent; //connect yth children
    if(!y->parent){
        x=t->root;
    }
    else{
        if(y==y->parent->left)
            y->parent->left=x;
        else
            y->parent->right=x;
    }
    if(y!=z)
        z->key=y->key;
    freeNode(y);
}

