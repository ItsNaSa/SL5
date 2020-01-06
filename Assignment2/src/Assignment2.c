/*
 ============================================================================
 Name        : Assignment2New.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#define MAXSIZE 99
//referenced tables
struct mottab mtab[14];	//mnemonic opcode table
struct pottab ptab[5];	//pseudo opcode table
struct registers reg[4];	//registers

//to be created tables
struct symtab stab[30];	//symbol table
struct littab ltab[10];	//literal table
struct pooltab pooltab[10];	//pool table
struct ic intermediateCode[25];	//intermediate code

int LC = 0;
int PTP=0,LTP=0,STP=0;	//pool table pointer, Literal table pointer, Symbol table pointer
int ICP=0;	//intermediate code pointer
char *words[5];

void set_literal_tab(int lit_id,char lit_name[20],int lit_adr){
	ltab[LTP].index = lit_id;
	strcpy(ltab[LTP].literal,lit_name);
	ltab[LTP].add = lit_adr;
	LTP++;
}

void label_found(){
	int location = -1;
	if((location=check_symtab(words[0])) > (-1)){	//if label found
		stab[location].address = LC;
	}
	else{	//else insert into the table
		stab[STP].index = STP+1;
		strcpy(stab[STP].symbol,first);
		stab[STP].address = LC;
		STP++;
	}
}

void start_found(){
	int code;
	if((code=check_ptab(words[1])) > -1)
		printf("(AD %d)",code);
	//if operand one is empty
	if(strcmp(words[2],"-")!=0){
		int address;
		sscanf(words[2],"%d",&address);	//convert address to integer form
		LC = address;	//Assign the operand one to LC
		printf(" (C %d)",LC);
	}
	strcpy(intermediateCode[ICP].second,"AD");	//create the intermediate code
	intermediateCode[ICP].third=code;
	strcpy(intermediateCode[ICP].sixth,"C");
	intermediateCode[ICP].seventh=LC;
}

void create_IC(int no_of_tokens){
	FILE *fptr1 = NULL;
	int label_index;
	int flag;
	int reg_no;
	int temp,symbol_index;
	int no_of_operands;
	char *mnemonicCode;
	char machine_code_temp[10];
	fptr1 = fopen("intermediateCode.txt","a");
		int location = -1;

		//if first word is not an Mnemonic -> it is a label
		if((location = check_mottab(words[0])) == (-1)){	//if first word is not a Mnemonic
			if((location = check_symtab(words[0])) == -1){	//if it also not in the symbol table
				stab[STP].index = STP+1;					//insert into the symbol table
				strcpy(stab[STP].symbol,words[0]);
				stab[STP].address = LC;
				STP++;
			}
			else{
				//if present, update the address
				label_index = location;
				stab[label_index].address = LC;
			}
			//if word[0] is not in MOT, then words[1] is the mnemonic code -> flag = 1 means that words[1] is mnemonic code
			flag = 1;
			location = check_mottab(words[1]);	//address of the mnemonic code, as decided above
		}

		//decide the mnemonic
		if(flag == 0){
			mnemonicCode = words[0];
		}
		else if(flag == 1){
			mnemonicCode = words[1];
		}

		//check the mnemonic
		if(strcmp(mnemonicCode,"START") == 0){	//if START statement
			LC = atoi(words[flag+1]);
			fprintf(fptr1,"(AD 1)(C %d)\n",LC);
		}
		else if(strcmp(mnemonicCode,"LTORG") == 0){	//if LTORG statement
			update_literal_table();
			fprintf(fptr1,"(AD 3)\n");
		}
		else if(strcmp(mnemonicCode,"ORIGIN") == 0){	//if ORIGIN
			temp = check_symtab(words[flag+1]);
			LC = stab[temp].address;
			fprintf(fptr1,"(AD 4)(C %d)\n",LC);
		}
		else if(strcmp(mnemonicCode,"EQU")==0){	//if EQU
			temp = check_symtab(words[0]);
			stab[temp].address = stab[check_symtab(words[2])].address;
			fprintf(fptr1,"(AD 5)\n");
		}
		else if(strcmp(mtab[location].class,"DL")==0){		//if class of mnemonic is DL
			//DS
			if(strcmp(mnemonicCode,"DS") == 0){
				temp = atoi(words[flag+1]);
				LC += temp;
				strcpy(stab[label_index].size,words[flag+1]);	//label_index is location of label in the symbol table
				fprintf(fptr1,"(DL 2)(C %d)\n",temp);
			}
			else if(strcmp(mnemonicCode,"DC")==0){
				LC++;
				strcpy(stab[label_index].size,words[flag+1]);
				fprintf(fptr1,"(DL 1)(C %s)\n",words[flag+1]);
			}
		}
		else if(strcmp(mtab[location].class,"IS")==0){	//if an imperative statement
			no_of_operands = no_of_tokens-(flag+1);
			strcpy(machine_code_temp,mtab[location].machine_code);
			fprintf(fptr1,"(IS %s)",machine_code_temp);
			for(int i = 0 ; i< no_of_operands;i++){
				if(isLiteral(words[flag+i])){
					set_literal_tab(LTP+1,words[flag+i],0);
					if(LTP < 10){
						fprintf(fptr1,"(L 0%d)",LTP);
					}
					else{
						fprintf(fptr1,"(L %d)",LTP);
					}
				}
				else if((reg_no = checkRegister(words[flag+i])) > 0){
					fprintf(fptr1,"(R 0%d)",reg_no);

				}
				else{
					symbol_index = check_symtab(words[flag+i]);
					if(symbol_index == -1){
						stab[STP].index = STP+1;					//insert into the symbol table
						strcpy(stab[STP].symbol,words[flag+i]);
						stab[STP].address = LC;
						symbol_index = STP;
						STP++;
					}
					if(symbol_index<10){
						fprintf(fptr1,"(S 0%d)",symbol_index);
					}
					else{
						fprintf(fptr1,"(S %d)",symbol_index);
					}
				}
			}
			fprintf(fptr1,"\n");
			LC = LC+1;
		}
		else if(strcmp(mnemonicCode,"END")==0)
		{
			updateLiteralTable();
			fprintf(fptr1,"(AD 02)\n");
			LC = LC+1;
		}
		printf("\nLC : %d\n",LC);
		printf("\nSTP : %d\n",STP);
		printf("\nLTP : %d\n",LTP);
		printf("\nPTP : %d\n",PTP);
		printSYMTAB();
		printLITTAB();
	fclose(fptr1);
}

int main(int argc, char *argv[]) {
	init(mtab,ptab,reg);
	FILE *input_file = NULL;
	int i;

	FILE *fptr1 = NULL;
	fptr1 = fopen("intermediateCode.txt","w");
	fclode(fptr1);

	input_file = fopen(argv[1],"r");	//argv[1] is ALP code file
	char str[99],token[15];
	while (fgets(str, MAXSIZE, input_file) != NULL){
		words[0]=words[1]=words[2]=words[3]= "\0";
		words = strtok(str,"\t");
		i = 0;
		while(token != NULL){
			words[i] = token;
			i++;
			token = strtok(NULL,"\t");
	  	}
		create_IC(i);
	}
	fclose(input_file);
}
