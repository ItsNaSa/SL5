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
struct mottab mtab[14];	//mnemonic opcode table
struct pottab ptab[5];	//pseudo opcode table
struct symtab stab[30];
struct littab ltab[10];
int size_of_mottab = 13;
struct registers reg[4];
int LC = 0;

int check_mottab(char token[10]){
	for(int i=0;i<size_of_mottab;i++){
		if(strcmp(mtab[i].mnemonic_code,token) == 0){
			return i;
		}
	}
	return -1;
}

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
	int location = 0;
	int this_address;
	struct ic intermediate;
	int this_code;	//the opcode of the current 
	FILE *fp;	//for insertion of Intermediate code

	//step 2A
	//if label is present, enter the pair (symbol, LC) into symbol table
	if(strcmp(tokens[0],"-") != 0){
		//if symbol is already present in the symbol table
		location = check_symtab(tokens[0],n);
		if(location > (-1)){	//if already present,
			stab[location].address = LC;		//update the address
			//s[location].length = tokens[2];	//possible error
		}
		else{	//if symbol is not found, add it to the symbol table
			strcpy(stab[*n].symbol,tokens[0]);
			stab[*n].address = LC;
			(*n)++;
		}

		//step 2D - If EQU is found, then
		if(strcmp(tokens[1],"EQU") == 0){
			//checks for the address of operand 1
			location = check_symtab(tokens[2],n);
			this_address = stab[location].address;
			//assign that address to the address of label
			location = check_symtab(tokens[0],n);
			stab[location].address = this_address;
		}
	}
//	step 2B
	if(strcmp(tokens[1],"LTORG")){
		step2B();
	}
//	step 2C
//	if start or origin statement
	if(strcmp(tokens[1],"START")==0 || strcmp(tokens[1],"ORIGIN")==0){
		LC = atoi(tokens[2]);
	}
//	step 2E
//	if a declaration statement is found,
	if(strcmp(tokens[1],"DS")==0 || strcmp(tokens[1],"DC")){
		fp = fopen("inter_code.txt","a");
		if(strcmp(tokens[1],"DC")==0){
			strcpy(intermediate.class,"DL");
			intermediate.code = 1;
			intermediate.constant = "C";
			strcpy(intermediate.constant_size,tokens[2]);
			LC = LC + 1;
		}
		else
		{
			strcpy(intermediate.class,"DL");
			intermediate.code = 2;
			int size = atoi(tokens[2]);
				location = check_symtab(tokens[0],n);
				stab[location].length = size;
				intermediate.constant = "C";
			strcpy(intermediate.constant_size,size);
			LC = LC+size;

		}
		fprintf(fp,"%s-%d-%s-%s\n",intermediate.class,intermediate.code,intermediate.constant,intermediate.constant_size);
		fclose(fp);
	}
	
	//if next is Mnemonic, go to step 2F
	step2F(tokens);
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

