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
struct registers reg[4];
int size_of_mottab = 13;
int size_of_littab = 0;
int size_of_reg = 4;
int LC = 0;


//called when LTORG is found
void step2B(){
	//TODO add the code for step2B
}

//called when mnemonic is found
int step2F(char *tokens[4]){
	int location = -1;
	int code;
	char *temp = tokens[2];
	char *temp2 = tokens[3];
	char this_literal[5];
	location = check_mottab(tokens[1]);
	if(location == -1)
		return -1;
	else
		code = mtab[location].machine_code;
	//check if literal
	//TODO check for both the operands
	if(check_literal(*temp2)){
		strcpy(ltab[size_of_littab].literal,tokens[3]);	//insert the literal in the literal table
		size_of_littab++;
		//TODO add the code to create the (intermediate code) if literal is found
	}
	//check if register
	if(check_register(*temp) != 0){
		//TODO create intermediate code if register is found
	}

	//check if symbol
	if((location=check_symtab(*temp)) > -1){
		//TODO generate IC if a symbol is there
		LC += stab[location].length;
	}
	else{
		//TODO add the entry in the symbol table
	}


}

void create_IC(char *tokens[4],int *n){
	int location = 0;
	int this_address;
	struct ic intermediate;
	int this_code;	//the opcode of the current 
	FILE *fp;	//for insertion of Intermediate code

	//	step 2C
	//	if start or origin statement
	//TODO What to do of ORIGIN LOOP1 + 9
	if(strcmp(tokens[1],"START")==0 || strcmp(tokens[1],"ORIGIN")==0){
		LC = atoi(tokens[2]);
	}

	//step 2A
	//if label is present, update the pair (symbol, LC) into symbol table
	if(strcmp(tokens[0],"-") != 0){
		//if symbol is already present in the symbol table
		location = check_symtab(tokens[0],n);
		if(location > (-1)){	//if already present,
			stab[location].address = LC;		//update the address
			//TODO check the next line
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
		//if next is a Mnemonic
		else if(check_mottab(tokens[1]) > -1){
			step2F(tokens);
		}
	}
//	step 2B
	if(strcmp(tokens[1],"LTORG")){
		step2B();
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
	
	//if Mnemonic, go to step 2F
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

