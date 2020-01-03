/*
 ============================================================================
 Name        : Assignment2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//check line 32,40
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#define MAXCHAR 100
struct mottab mtab[14];
struct pottab ptab[5];
struct symtab stab[15];
struct registers reg[4];
int LC = 0;

int check_symtab(char token[10], int *number){
	int n = *number;
	for(int i = 0 ;i< n;i++){
		if(strcmp(stab[i].symbol,token)==0){
			return i;
		}
	}
	return (-1);
}

void create_IC(char *tokens[4],int *n){
	char this_label[10];
	int location = 0;
	int this_address;
	//step 2A
	//if label is present
	if(strcmp(tokens[0],"-") != 0){
		strcpy(this_label,tokens[0]);
		//if symbol is already present in the symbol table
		location = check_symtab(this_label,n);
		if(location > (-1)){
			stab[location].address = LC;
			//s[location].length = tokens[2];	//possible error
		}
		else{	//if symbol is not found, add it to the symbol table
			strcpy(stab[*n].symbol,tokens[0]);
			stab[*n].address = LC;
			(*n)++;
		}
		//if next is Mnemonic, go to step 2F

		//		step 2D - If EQU is found, then
		if(strcmp(tokens[1],"EQU") == 0){
			//checks for the address of operand 1
			location = check_symtab(tokens[2],n);
			this_address = stab[location].address;
			//assign that address to the address of label
			location = check_symtab(tokens[0],n);
			stab[location].address = this_address;
		}

	}
////	step 2B
//	if(strcmp(tokens[1],"LTORG")){
//
//	}
////	step 2C
////	if start or origin statement
//	if(strcmp(tokens[1],"START")==0 || strcmp(tokens[1],"ORIGIN")==0){
//		LC = atoi(tokens[2]);
//	}
////	step 2E
////	if a declaration statement is found,
//	if(strcmp(tokens[1],"DS")==0 || strcmp(tokens[1],"DC")){
//
//	}
//	//end is encountered
//
printf("\n\n\nEnd of IC function\n\n\n");
}

int main(int argc,char *argv[]) {
	init(mtab,ptab,reg);
	char str[100];
	char *tokens[4];
	char *token;
	int i;
	int end_found = 0;
	int number_of_symbols=0;

	FILE *input_file = NULL;
	input_file = fopen(argv[1],"r");	//argv[1] is ALP code file

	while (fgets(str, MAXCHAR, input_file) != NULL){
		tokens[0]=tokens[1]=tokens[2]=tokens[3]= "\0";
		token = strtok(str,"\t");
		i = 0;
		while(token != NULL){
			tokens[i] = token;
			i++;
			// printf("%s\n",token);
			token = strtok(NULL,"\t");
	  	}
		// printf("0. %s, 1. %s, 2. %s, 3. %s\n",tokens[0],tokens[1],tokens[2],tokens[3]);
		create_IC(tokens,&number_of_symbols);
	}
	printf("\nBAck to main function\n");
	for(int i = 0;i<number_of_symbols;i++){
		printf("Symbol = %s, Address = %d, Length = %d\n",stab[i].symbol,stab[i].address,stab[i].length);
	}
	
	return EXIT_SUCCESS;
}

