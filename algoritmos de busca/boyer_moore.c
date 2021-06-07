#ifndef BOYER_MOORE
#define BOYER_MOORE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ASIZE 512


long long boyer_moore(char *text,char *pattern, long long text_length){
	long long pattern_length, badCharShift[ASIZE];
	long long count=0;
	long long h;
	
	pattern_length = strlen(pattern);
	//preprocessamento
	for(long long i = 0;i<ASIZE;i++)
		badCharShift[i]=pattern_length;

	int index;
	for(long long i = 0;i<pattern_length-1;i++){
		h = ((long long)pattern[i])%ASIZE;
		if(h<0)
			h=0;
		badCharShift[h]=pattern_length-i-1;

	}
	
	//printf("preprocessamento pronto\n[");
	//for(long long i=0; i<ASIZE;i++){
	//	printf("%d ",badCharShift[i]);
	//}
	//printf("]\n");
	
	long long i = pattern_length - 1;
	long long j;
	
	
	//printf("text length = %d\n",text_length);
	
	while(i<text_length){
		
		j=0;
	
		while(j<pattern_length && text[i-j]==pattern[pattern_length-j-1]){
			j++;
			
		}
		if(j==pattern_length){
			//printf("Padrao encontrado em %lld.\n",i-pattern_length+1);
			//printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i-pattern_length+1);
			count++;
		}
		h = ((long long)text[i])%ASIZE;
		if(h<0)
			h=0;
		
		i = i+badCharShift[h];
	}
	
	//printf("i= %d  textlength = %d\n",i, text_length);
	
	//printf("BOYER_MOORE: Palavras=padrao encontradas: %d\n",count);
	
	return count;
	
}

#endif