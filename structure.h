#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node NODE;

typedef struct Key{
    int key;
    char* data;
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
    void (*next)(struct Iterator *);
    int isLast;
} I;

TREE* createTree();
NODE* addNode(TREE* t, int k);
I* createIterator(TREE* t);
NODE* treeMin(NODE* r);
NODE* treeMax(NODE* r);
NODE* getNode(TREE* t, int key);
void deleteNode(TREE* t, NODE** z);