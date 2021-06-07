#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(){
	
	char alfabeto[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	int limit = strlen(alfabeto)-1;
	
	int divisor = RAND_MAX/(limit+1);
    int retval;
	
	srand(time(NULL));
	
	FILE *fp;
	
	fp = fopen("randText.txt","w");
	
	for(int i=0;i<5000000;i++){
		
    do { 
        retval = rand() / divisor;
    } while (retval > limit);
	
	fprintf(fp,"%c", alfabeto[retval]);
	
	}

}