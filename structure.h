#include <stdio.h>

typedef struct Node NODE;

typedef struct Key{
    char* key;
    int n;
} KEY;

struct Node{
    KEY* key;
    NODE* next;
    NODE* prev;
};

typedef struct Iterator{
    NODE* (*next)();
    NODE* current;
    int isEnd;
} ITERATOR;

NODE* listInit(char* key){

}

NODE* listAdd(char* key){

}

NODE* listInsert(NODE* head, NODE* x){

}

NODE* listDelete(NODE* x){

}

NODE* nextElement(ITERATOR* i){

}