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
#include <ctype.h>
#include "structures.h"
#define MAXSIZE 99

void create_IC(int no_of_tokens){
	FILE *fptr1 = NULL;	//for writing in the file
	int label_index;
	int flag=0;	//for position of operands in line
	int reg_no=0;
	int temp=-1,symbol_index=-1;
	int no_of_operands=0;
	char *mnemonicCode=NULL;
	int machine_code_temp;

	fptr1 = fopen("intermediateCode.txt","a");
		int location = -1;
		//if first word is not an Mnemonic -> it is a label
		if((location = check_mottab(words[0])) == (-1)){	//if first word is not a Mnemonic -> check if a symbol
			// printf("Word \"%s\" is not a Mnemonic\n",words[0]);
			if((location = check_symtab(words[0])) == (-1)){	//if it also not in the symbol table -> add to the symbol table
				printf("Word \"%s\" is not a available Symbol\n",words[0]);
				stab[STP].index = STP+1;					//insert into the symbol table
				strcpy(stab[STP].symbol,words[0]);
				stab[STP].address = LC;
				label_index = STP;
				STP++;
			}
			else{
				//if present, update the address
				label_index = location+1;
				stab[label_index].address = LC;
			}
			//if word[0] is not in MOT => it is a symbol, then words[1] is the mnemonic code -> flag = 1 means that words[1] is mnemonic code
			flag = 1;
			location = check_mottab(words[1]);	//address of the mnemonic code, as decided above
		}	//end of mnemonic and symbol check
		
		//decide which word is the mnemonic
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
			start_found = 1;
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
				printf("DS encounterd.... Size of statement is %d\n",temp);
				LC += temp;
				// strcpy(stab[label_index].size,words[flag+1]);
				printf("DS : words[flag+1] = %s, label_index is %d\n",words[flag+1],label_index);	//label_index is location of label in the symbol table
				sscanf(words[flag+1],"%d",&stab[label_index].size);
				fprintf(fptr1,"(DL 2)(C %d)\n",temp);
			}
			else if(strcmp(mnemonicCode,"DC")==0){
				LC++;
				// strcpy(stab[label_index].size,words[flag+1]);
				sscanf(words[flag+1],"%d",&stab[label_index].size);
				fprintf(fptr1,"(DL 1)(C %s)\n",words[flag+1]);
			}
		}
		else if(strcmp(mtab[location].class,"IS")==0){	//if an imperative statement
			no_of_operands = no_of_tokens- flag-1;
			printf("No. of tokens is %d,No. of operands is %d\n",no_of_tokens,no_of_operands);
			// strcpy(machine_code_temp,mtab[location].machine_code);
			machine_code_temp = mtab[location].machine_code;
			fprintf(fptr1,"(IS %d)",machine_code_temp);
			for(int i = 1 ; i<= no_of_operands;i++){
				printf("Flag is %d, i is %d\n",flag,i);

				printf("The word is now %s\n",words[flag+i]);
			//check if literal, register or symbol
				if(isLiteral(words[flag+i])){
					set_literal_tab(LTP+1,words[flag+i],0);
					if(LTP < 10){
						fprintf(fptr1,"(L 0%d)",LTP);
					}
					else{
						fprintf(fptr1,"(L %d)",LTP);
					}
				}
				else if((reg_no = check_register(words[flag+i])) > 0){
					fprintf(fptr1,"(R 0%d)",reg_no);

				}
				else{
					symbol_index = check_symtab(words[flag+i]);
					printf("Symbol Index of %s is %d\n",words[flag+i],symbol_index);
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
			update_literal_table();
			fprintf(fptr1,"(AD 02)\n");
			LC = LC+1;
			end_found = 1;	//flag to check if END is there or not
		}
		printf("\nLC : %d\n",LC);
		// printf("\nSTP : %d\n",STP);
		printSYMTAB();
		printLITTAB();
		print_pooltab();
	fclose(fptr1);
}

int main(int argc, char *argv[]) {
	init(mtab,reg);
	FILE *input_file = NULL;
	int i;
	int length;

	FILE *fptr1 = NULL;
	fptr1 = fopen("intermediateCode.txt","w");
	fclose(fptr1);

	input_file = fopen(argv[1],"r");	//argv[1] is ALP code file
	char str[99],*token;
	while (fgets(str, MAXSIZE, input_file) != NULL){
		words[0]=words[1]=words[2]=words[3]= "\0";
		token = strtok(str," ");
		i = 0;
		while(token != NULL){
			length = strlen(token);
			for(int i = 0;i<length;i++){
				if(token[i] == '\n')
					token[i] = '\0';
			}
			words[i] = token;
			i++;
			token = strtok(NULL," ");
	  	}
		create_IC(i);
	}
	if(!start_found){
		printf("Error!!! Program should contain START statement...!!! START TO THE PROGRAM NOT FOUND!!!!\n");
		FILE* fptr1 = NULL;
		remove("symtab.txt");
		remove("littab.txt");
		remove("pooltab.txt");
	}
	if(!end_found){
		printf("Error!!! Program should contain END statement...!!! END NOT FOUND!!!!\n");
		remove("symtab.txt");
		remove("littab.txt");
		remove("pooltab.txt");
	}
	fclose(input_file);
}
