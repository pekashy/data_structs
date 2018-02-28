#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>
#include <ctype.h>
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
    TREE* T=createBtree(3);
    printf("hello\n");
	while(read(file, &c, 1)!=0){
		if((c==' ' || c=='\n' || c=='-') && strlen(word)!=0){
			addNode(T, word);
            printf("%s\n", word);
            memset(word, '\0', ((int) st.st_size)*sizeof(char));
			it=word;
		}
		if(c>=65 && c<=90) c=(char) tolower(c);
        //printf("%c %d %s\n", c, c, word);
        if(c>=97 && c<=122){
			*it=c;
			it++;
		}
	}

}