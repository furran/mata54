#ifndef BOYER_MOORE
#define BOYER_MOORE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ASIZE 256 // tamanho do alfabeto ascii

int boyer_moore(char *text,char *pattern){
	int pattern_length, text_length, badCharShift[ASIZE];
	
	pattern_length = strlen(pattern);
	text_length = strlen(text);
	//preprocessamento
	for(int i = 0;i<ASIZE;i++)
		badCharShift[i]=pattern_length;
	for(int i = 0;i<pattern_length-1;i++)
		badCharShift[(int)pattern[i]]=pattern_length-i-1;
	
	int i = pattern_length - 1;
	int j;
	
	while(i<text_length){
		j=0;
		while(j<pattern_length && text[i-j]==pattern[pattern_length-j-1]) 
			j++;
		if(j==pattern_length){
			printf("Padrao encontrado em %d.\n",i-pattern_length+1);
			printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i-pattern_length+1);	
		}
		i = i+badCharShift[(int)text[i]];
	}
	
	
}

#endif