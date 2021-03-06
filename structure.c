#include <memory.h>
#include "structure.h"

void freeNode(NODE** n){
    //if(!(*n))
    //    return; //safe
    (*n)->parent=NULL;
    (*n)->left=NULL;
    (*n)->right=NULL;
    if((*n)->key){
        free((*n)->key->data);
        (*n)->key->data=NULL;
    }
    free((*n)->key);
    (*n)->key=NULL;
    free((*n));
    (*n)=NULL;
    //printf("%d", n->isLeaf);

}

NODE* getNode(TREE* t, int key){
    NODE* n=t->root;
    if(!n->key)
        return NULL;
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
    if(!n)
        return NULL;
    if(!n->key)
        return n;
    while(n->left)
        n=n->left;
    return n;
}

NODE* treeMax(NODE* r){
    NODE* n=r;
    if(!n)
        return NULL;
    if(!n->key)
        return n;
    while(n->right)
        n=n->right;
    return n;
}

NODE* createNode(){
    NODE* n=malloc(sizeof(NODE));
    if(!n)
        return NULL;
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
    if(!t)
        return NULL;
    t->root=createNode();
    if(!t->root){
        free(t);
        return NULL;
    } //not enough memory
    t->root->parent=NULL;
    return t;
}

NODE* treeInsert(TREE* t, NODE* z){
    NODE* x=t->root; //always present
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
        freeNode(&x);
    }
    else{
        x->isLeaf=0;
        z->inList=1;
        z->parent=x;
        if(z->key->key < x->key->key)
            x->left=z;
        if(z->key->key == x->key->key){
            x->key->n=x->key->n+1;
            freeNode(&z);
            return x;
        }
        if(z->key->key>x->key->key)
            x->right=z;
    }
    return z;
}

KEY* createKey(int k){
    KEY* key=malloc(sizeof(KEY));
    if(!key)
        return NULL;
    key->n=1;
    key->key=k;
    key->data=malloc(64000); //data
    if(!key->data){
        free(key);
        return NULL;
    }
    memset(key->data, '1', 64000);
    return key;
}

NODE* addNode(TREE* t, int k){
    if(!t)
        return NULL;
    if(!t->root)
        return NULL;
    KEY* key =createKey(k);
    if(!key){
        return NULL;
    }
    NODE *n = createNode();
    if(!n) {
        free(key);
        return(NULL);
    }
    n->key=key;
    NODE* ins=treeInsert(t, n);
    if(!ins){
        freeNode(&n);
        return NULL;
    }
    else
        return ins;
}

NODE* nextElement(NODE* x){
    if(!x)
        return NULL;
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
    if(!i)
        return;
    i->current=(nextElement(i->current));
    if(!i->current)
        i->isLast=1;
}

I* createIterator(TREE* t){
    I* i=malloc(sizeof(I));
    if(!i)
        return NULL;
    i->t=t;
    i->current=treeMin(t->root);
    i->next=&next;
    i->isLast=0;
    return i;
}

void deleteNode(TREE* t, NODE** z){
    NODE *x, *y;
    if(!z)
        return;
    if(!(*z))
        return;
    if(!(*z)->left && !(*z)->right && !(*z)->parent){
        freeNode(z);
        *z=NULL;
        return;
    }
    if(!(*z)->left || !(*z)->right)
        y=*z;
    else
        y=nextElement(*z);
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
    if(y!=*z)
        (*z)->key=y->key;

    freeNode(&y);
}
