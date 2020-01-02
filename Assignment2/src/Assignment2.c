/*
 ============================================================================
 Name        : Assignment2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#define MAXCHAR 100
struct mottab mtab[14];
struct pottab ptab[5];
struct symtab stab[15];
struct registers reg[4];

void create_IC(char *arr[4]){
	
}

int main(int argc,char *argv[]) {
	init(mtab,ptab,reg);
	char str[100];
	char *tokens[4];
	char *token;
	int i;

	FILE *input_file = NULL;
	input_file = fopen(argv[1],"r");	//argv[1] is ALP code file

	  	while (fgets(str, MAXCHAR, input_file) != NULL){
			tokens[1]=tokens[2]=tokens[3]=tokens[0] = "\0";
			token = strtok(str,"\t");
		  	i = 0;
		  	while(token != NULL){
				tokens[i] = token;
				i++;
				// printf("%s\n",token);
				token = strtok(NULL,"\t");
		  	}
			printf("0. %s, 1. %s, 2. %s, 3. %s\n",tokens[0],tokens[1],tokens[2],tokens[3]);
			create_IC(tokens);
	  	}
	
	return EXIT_SUCCESS;
}

