#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structure.h"

int main(){
    char filename[]="source";
    int file=open(filename, O_RDONLY);
    printf("hello %d\n", file);
    struct stat st;
    stat(filename, &st);
    printf("hello %d\n", st.st_size);
    char* word=malloc(((int) st.st_size)*sizeof(char));
    char* it=word;
    char c;
    //printf("hello %d\n", sizeof(TREE));
    TREE* tree=createTree();
    srand(time(NULL));//temporary
    for(int i=0; i<100; i++){
        addNode(tree, rand() % (10 + 1 - 1) + 1);
    }

}
