#ifndef BRUTE_FORCE
#define BRUTE_FORCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int brute_force(char *text,char *pattern){
    size_t i,j,text_length, pattern_length;
    text_length = strlen(text);
    pattern_length = strlen(pattern);
    int lines = 1;
    size_t n = text_length - pattern_length;

    for(i=0;i<=n;i++){
        if(text[i]=='\n'){
            lines++;
        }
        if(strncmp(pattern,text+i,pattern_length) == 0){
			printf("Padrao encontrado em %d.\n",i);
			printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i);
		}
    }
}

#endif