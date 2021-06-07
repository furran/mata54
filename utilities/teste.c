#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "boyer_moore.c"
#include "KMP.c"
#include "rabin_karp.c"
#include "brute_force.c"

int main(){
    char filename[999];
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
       
	
	size_t count;
	
    buffer = (char*)malloc (sizeof(char)*length);
    if (buffer){
        count = fread (buffer, 1, length, fp);
		
		printf("count: %I64u length: %I64u\n", count, length);
    }
	else {
		perror("Falha em alocar memoria.\n");
		exit(EXIT_FAILURE);
	}
	
	
	
	fclose(fp);
	
	fp = fopen("checksum.txt","w");
	
	if(fp==NULL){
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }
	
	for(int i=0;i<count;i++)
		fprintf(fp,"%c",buffer[i]);
	
	
	
    printf("Insira o padrao a ser buscado:\n");
	char tmp;
    char pattern[1000];
	//scanf("%s",pattern);
	scanf("%c", &tmp);
    fgets(pattern,1000,stdin);
	printf("tmp = %c", tmp);
    printf("%s\n",pattern);
	
	printf("strln1:%I64u\n", strlen(pattern));

	pattern[strlen(pattern)-1] = '\0';
	
	printf("%s\n", pattern);
	
	printf("strln2:%I64u\n",strlen(pattern));

    printf(">> Brute Force: \n");

    printf("%I64d\n", brute_force(buffer, pattern,count));
	
	

    printf(">> Rabin-Karp: \n");
    
    printf("%I64d\n",rabin_karp(buffer,pattern,-1,count));
	
	
	printf(">> KMP:\n");
	
	 printf("%I64d\n",knuth_morris_pratt(buffer,pattern,count));
	
	printf(">> Boyer-Moore: \n");
	
	 printf("%I64d\n",boyer_moore(buffer,pattern,count));
	
}