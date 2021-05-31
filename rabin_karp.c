#ifndef RABIN_KARP
#define RABIN_KARP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



#define ASIZE 256 //tamanho do alfabeto

#define PRIME 7919 // 7919*256=2027264<2^32-1

int rabin_karp(char *text, char *pattern, int d, int prime){
    int text_length, pattern_length,j;
	
	d = ASIZE;
	prime = 7219;
	
    text_length = strlen(text);
    pattern_length = strlen(pattern);

    int n = text_length - pattern_length;

    int h = 1; //
    int p = 0; //'hash' do padrao
    int t = 0; //'hash' do bloco de texto atual

    for(int i = 0;i<pattern_length-1;i++){
        h = (h*d)%prime;
    }

    //pre-processamento
    for(int i = 0;i<pattern_length;i++){
        p = (d*p+pattern[i])%prime;
        t = (d*t+text[i])%prime;
    }

    printf("preprocessamento:\n p = %d, t =  %d, h = %d\n",p,t,h);

    //busca do padrao
    for(int i=0;i<=n;i++){
        if(p == t && strncmp(pattern,text+i,pattern_length)==0){
			printf("Padrao encontrado em %d.\n",i);
			printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i);
		}
        if(i<=n){
            t = (d*(t-text[i]*h)+text[i+pattern_length])%prime;
			if(t<0){
				t= t+prime;
			}
        }
    }

}

#endif