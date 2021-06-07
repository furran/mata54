#ifndef BRUTE_FORCE
#define BRUTE_FORCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long brute_force(char *text,char *pattern, size_t text_length){
	long long count = 0;
    long long i, pattern_length;
    pattern_length = strlen(pattern);
    //long long lines = 1;
    long long n = text_length - pattern_length;

    for(i=0;i<=n;i++){
        //if(text[i]=='\n'){
         //   lines++;
        //}
        if(strncmp(pattern,text+i,pattern_length) == 0){
			count++;
			//printf("Padrao encontrado em %I64d.\n",i);
			//printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i);
		}
    }
	
	//printf("BRUTE_FORCE: Palavras=padrao encontradas: %d\n",count);
	return count;
}

#endif