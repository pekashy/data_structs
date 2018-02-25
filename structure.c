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
	struct stat st;
	stat(filename, &st);
	char* word=malloc(st.st_size*sizeof(char));
	char* beg=word;
	char c;
	while(read(file, &c, 1)!=0){
		if(c==' ' || c=='\n' || c=='-'){
			addNode(word);
			word=beg;
		}
		if(c>=65 && c<=90) tolower(c);
		if(c>=97 && c<=122){
			*word=c;
			word++;
		}
	}
}