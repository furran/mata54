#ifndef KNUTH_MORRIS_PRATT
#define KNUTH_MORRIS_PRATT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int knuth_morris_pratt(char *text, char *pattern){
	int pattern_length,text_length;
	
	pattern_length = strlen(pattern);
	text_length = strlen(text);
	
	int pi[pattern_length];
	
	int k=-1;

	//preprocessamento 
	if(pattern_length > 0) pi[0] = -1;
	
	for(int q=1; q<pattern_length;q++){
		//printf("antes>> q: %d k: %d\n",q,k);
		while(k>=0 && pattern[k+1]!=pattern[q]){
			//printf("AQUI k= %d , P[%d]=%c e P[%d]=%c\n",k,k+1,pattern[k+1],q,pattern[q]);
			k=pi[k];
		}
		if(pattern[k+1]==pattern[q])
			k=k+1;
		pi[q]=k+1;
		
		//printf("pos>> q: %d k: %d\n",q,k);
	}
	//printf("pi[]={ ");
	
	//for(int i=0;i<pattern_length-1;i++){
	//	printf("%d |",pi[i]);
	//}
	
	//printf("%d }\n", pi[pattern_length-1]);

	//busca do padrao
	
	for(int i=0,j=-1;i<text_length;i++){
		
		
		//printf(">>%s | %*.*s\n",pattern, pattern_length, pattern_length, text+i);
		//printf("%d: j=%d\n",i,j);
		while(j>=0 && pattern[j+1]!=text[i]){
			//printf("pi[%d]=%d\n",j,pi[j]);
			j=pi[j];
		}
		if(pattern[j+1]==text[i]){
			j=j+1;
			//printf("MATCH:j= %d\n", j);
		}
		
		if(j==pattern_length-1){
			printf("Padrao encontrado em %d.\n",i-pattern_length+1);
			printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i-pattern_length+1);
			j=pi[j];
		}
	}
	
}

#endif