#include <stdio.h>
#include <string.h>

typedef struct Node NODE;

typedef struct Key{
    char* key;
    int data;
} KEY;

struct Node{
	int notLeaf; //is notLeaf (0 or 1)
	int n; //number of node's keys
	KEY** key; //node's keys, borders, that split subtrees values |2t-1 max|
	NODE** c; //pointers to the node's children  |2t max|
};

typedef struct Tree{
	int t;//the minimum power of the node
	NODE* root;
} TREE;

typedef struct Iterator{
    NODE* (*next)();
    NODE* current;
    int isEnd;
} ITERATOR;

NODE * BTreeInsert(TREE *T, KEY* k);


NODE* addNode(TREE* T, char* word){
    KEY* k=malloc(sizeof(KEY));
    k->key=malloc(sizeof(char)*strlen(word));
    strcpy(k->key, word);
    //k->key=word;
    k->data=1;
    NODE* s=BTreeInsert(T, k);
    return s;
}

NODE* allocNode(int n, TREE* T){
	NODE* node=	(NODE*) malloc(sizeof(NODE));
	node->c=(NODE**) malloc((2*T->t)*sizeof(NODE*));
    node->key=(KEY**) malloc((2*T->t-1)*sizeof(KEY*));
    for(int i=0; i<n; i++){
        node->key[i]=(KEY*) malloc(sizeof(KEY));
        node->key[i]->data=0;
    }
    return node;
}

int compareKeys(KEY* key1, KEY* key2){
    int i=0;
    while(*(key1->key+i)==*(key2->key+i)){
        i++;
        if(*(key1->key+i)=='\0' || *(key2->key+i)=='\0') return 0;
    }
    if(*(key1->key+i)>*(key2->key+i)) return 1;
    else return -1;
}

void BTreeSplitChild(NODE* x, int i, NODE* y, TREE* T){//y is full node; x is its nonfull parent x->c[i]=y; z is its new parent
    int t= (y->n+1)/2-1;
	NODE* z=allocNode(t-1, T);//allocating node with t-1 keys (y has data=2t-1 keys)
    z->notLeaf=y->notLeaf;
    for(int j=0; j<t; j++) {
        z->key[j] = y->key[j + t]; //moving the right half of keys from y to z #|until j+t-1th|
        if (!y->notLeaf) {
            z->c[j] = y->c[j+t];
        }
    }
    if (y->notLeaf) z->c[t] = y->c[t+t]; //the last one  j=t
    y->n=t-1;  //changing the node y
    for(int j=x->n; j>i; j--)
        x->c[j]=x->c[j-1];//moving right until x->c[i+1] <= x->c[i]
    x->c[i]=z; //connecting new children node z to x next to the old one (y)
    for(int j=x->n-1; j>i; j--)
        x->key[j]=x->key[j-1];    //moving keys in x right by one
    x->key[i]=y->key[t-1]; //connecting median (t-th) key to the given i(i is index) position
    x->n=x->n+1; //we just added one another element to x on ith place, right?
}

void BTreeInsertNonfull(NODE* x, KEY* k, TREE* T){ //adding element [k] to the subtree with the non-full root [x]
	int i=x->n;
	if(!x->notLeaf) {//if x is the leaf, we just add key k to it
        if (x->n != 0) {
            while (i >= 1 && compareKeys(x->key[i-1], k) > 0) {//сдвигаем элементы вправо
                x->key[i] = x->key[i - 1];//moving the keys right
                i--;
            }
            if (compareKeys(x->key[i-1], k) == 0 && i!=1) {//key already exists in tree
                x->key[i-1]->data = x->key[i-1]->data + 1;
            } else {
                x->key[i] = k; //вставляем наш ключ слева
                x->n = x->n + 1;
            }
        } else { //empty node
            x->key[i] = k; //вставляем наш ключ слева
            x->n = x->n + 1;
        }
    }
	else{//or we are adding x to the subtree, whose root is the x's child, searching for the appropriate child
        while(i>=1 && compareKeys(x->key[i-1], k)>0)
            i--;
        i++;
        if(x->c[i-1]->n==(2*T->t-1)){ //if the child is the full node, then we split it to the 2 half-fool nodes
            BTreeSplitChild(x, i-1, x->c[i-1], T);
            if(compareKeys(k, x->key[i-1])<0)//determining in which of the new subtrees' we are adding x
                i++;
        }
        BTreeInsertNonfull(x->c[i-1], k, T);
	}
}

NODE * BTreeInsert(TREE *T, KEY* k){
    NODE* r=T->root;
    NODE* s;
    if(r->n==(2*T->t-1)){ //if the root has maximum number of children
        s=allocNode(1, T);
        T->root=s;
        s->notLeaf=0;
        s->n=0;
        s->c[0]=r;//growing up a new root, pointing the old one to it as a child
        for(int i=1; i<2*T->t; i++){
            s->c[i]=allocNode(1, T);
          //  s->c[i]->notLeaf=1;
        }
        BTreeSplitChild(s, 0, r, T); //connecting to the main root to the first position; i IS THE INDEX NOT THE NUMBER OF POSITION
        BTreeInsertNonfull(s, k, T);
    }
    else
        BTreeInsertNonfull(r,k,T);
    return s;
}

TREE* createBtree(int t){
    TREE* T=malloc(sizeof(TREE));
    T->t=t;
    T->root=allocNode(0, T);
    T->root->notLeaf=0;
    T->root->n=0;
    return T;
}

ITERATOR createIterator(TREE* T, NODE* (*next)()){

}

NODE* next(){

}


//TODO: iterator
//TODO: getMax
