#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#include "boyer_moore.c"
#include "KMP.c"
#include "rabin_karp.c"
#include "brute_force.c"


int main(){
    char filename[1000];
    char *text = 0;
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
	
    text = (char*)malloc (sizeof(char)*length);
    if (text){
        count = fread (text, 1, length, fp);
		
		printf("count: %I64d length: %I64d\n", count, length);
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
		fprintf(fp,"%c",text[i]);
	
	fclose(fp);
	
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
	
	int n = 10000;
	
	LARGE_INTEGER starting_time, ending_time, elapsed_microseconds, frequency;
	
	char str[] = "resultados_KMP_";

	
	if(strlen(pattern)<100)
		strcat(str,pattern);
	else strcat(str,"verylong");
	
	strcat(str,"_");
	
	strcat(str,filename);
	fp = fopen(str,"w");
	for(int i = 0; i<n;i++){
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&starting_time);
		//brute_force(text,pattern,count);
		//knuth_morris_pratt(text,pattern,count);
		//rabin_karp(text,pattern,-1,count); 
		//boyer_moore(text,pattern,count);
		QueryPerformanceCounter(&ending_time);
		elapsed_microseconds.QuadPart = ending_time.QuadPart - starting_time.QuadPart;
		elapsed_microseconds.QuadPart *= 1000000; //convertendo para microsegundos.
		elapsed_microseconds.QuadPart /= frequency.QuadPart; //dividindo pelo número de Ticks.
	
		fprintf(fp,"%I64d\n",elapsed_microseconds.QuadPart);
	}
	
	

}