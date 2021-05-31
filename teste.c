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
            printf("linhas lidas: %d\n", lines);
            return i;
		}
    }
    printf("Padrao nao encontrado. Linhas lidas: %d\n", lines);
    return -1;
}

int rabin_karp(char *text, char *pattern, int d, int modulus){
    int text_length, pattern_length,j;

    text_length = strlen(text);
    pattern_length = strlen(pattern);

    int n = text_length - pattern_length;

    int h = 1; //
    int p = 0; //'hash' do padrao
    int t = 0; //'hash' do bloco de texto atual

    for(int i = 0;i<pattern_length-1;i++){
        h = (h*d)%modulus;
    }

    //pre-processamento
    for(int i = 0;i<pattern_length;i++){
        p = (d*p+pattern[i])%modulus;
        t = (d*t+text[i])%modulus;
    }

    printf("preprocessamento:\n p = %d, t =  %d, h = %d\n",p,t,h);

    //busca do padrao
    for(int i=0;i<=n;i++){
        if(p == t && strncmp(pattern,text+i,pattern_length)==0){
			printf("Padrao encontrado em %d.\n",i);
			printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i);
			return i;
		}
        if(i<=n){
            t = (d*(t-text[i]*h)+text[i+pattern_length])%modulus;
			if(t<0){
				t= t+modulus;
			}
        }
    }
    printf("bad\n");
    return -1;

}

int knuth_morris_pratt(char *text, char *pattern){
	int pattern_length,text_length;
	
	pattern_length = strlen(pattern);
	text_length = strlen(text);
	
	int pi[pattern_length+1];
	
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
		//printf("%d |",pi[i]);
	//}
	
	//printf("%d }\n", pi[pattern_length-1]);
	
	
	//busca do padrao
	int i=0,j=0,m=pattern_length,n=text_length;
	
	while (i < text_length) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
  
        if (j == pattern_length) {
            printf("Found pattern at index %d ", i - j);
            j = pi[j - 1];
        }
        else if (i < text_length && pattern[j] != text[i]) {

            if (j != 0)
                j = pi[j - 1];
            else
                i = i + 1;
        }
    }
	/*
	for(int i=0,j=-1;i<text_length;i++){
		while(j>=0 && pattern[j+1]!=text[i])
			j=pi[j];
		if(pattern[j+1]==text[i]){
			j=j+1;
		}
		
		printf("%s | %*.*s\n",pattern, pattern_length, pattern_length, text+i);
		
		if(j==pattern_length){
			printf("Padrao encontrado em %d.\n",i);
			printf("Padrao: %*.*s\n",pattern_length, pattern_length, text+i);
			j=pi[j];
		}
	}
	*/
}

int pi(char *text,char *pattern){
		int pattern_length,text_length;
	
	pattern_length = strlen(pattern);
	text_length = strlen(text);
	
	int pi[pattern_length+1];
	
	int k=-1;

	//preprocessamento 
	if(pattern_length > 0) pi[0] = -1;
	
	for(int q=1; q<pattern_length;q++){
		printf("antes>> q: %d k: %d\n",q,k);
		while(k>=0 && pattern[k+1]!=pattern[q]){
			printf("AQUI k= %d , P[%d]=%c e P[%d]=%c\n",k,k+1,pattern[k+1],q,pattern[q]);
			k=pi[k];
		}
		if(pattern[k+1]==pattern[q])
			k=k+1;
		pi[q]=k+1;
		
		printf("pos>> q: %d k: %d\n",q,k);
	}
	printf("pi[]={ ");
	
	for(int i=0;i<pattern_length-1;i++){
		printf("%d |",pi[i]);
	}
	
	printf("%d }\n", pi[pattern_length-1]);
	
	
}



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
    
    rabin_karp(buffer,pattern,10,13);
	
	printf(">> pi[]:\n");
	
	pi(buffer,pattern);
	
	printf(">> KMP:\n");
	
	knuth_morris_pratt(buffer,pattern);

}