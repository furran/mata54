#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "boyer_moore.c"
#include "KMP.c"
#include "rabin_karp.c"
#include "brute_force.c"

int main(){
    char filename[100];
    char *buffer = 0;
    FILE *fp;

    printf("Insira o nome do arquivo:\n");
    scanf("%s",&filename);
    
    fp = fopen(filename,"r");
    if(fp==NULL){
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    fseek (fp, 0, SEEK_END);
    size_t length = ftell(fp);
    fseek (fp, 0, SEEK_SET);
        
    buffer = malloc (length);
    if (buffer){
        fread (buffer, 1, length, fp);
    }

    printf("Insira o padrao a ser buscado:\n");

    char pattern[256];


    scanf("%s",pattern);

    printf("%s\n",pattern);

    printf(">> Brute Force: \n");

    brute_force(buffer, pattern);

    printf(">> Rabin-Karp: \n");
    
    rabin_karp(buffer,pattern,256,7919);
	
	//printf(">> pi[]:\n");
	
	//pi(buffer,pattern);
	
	printf(">> KMP:\n");
	
	knuth_morris_pratt(buffer,pattern);
	
	printf(">> Boyer-Moore: \n");
	
	boyer_moore(buffer,pattern);

}