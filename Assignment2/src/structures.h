/*
 * structures.h
 *
 *  Created on: 06-Jan-2020
 *      Author: krish
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#define SIZE 99
#include <string.h>
#include <ctype.h>

//structure for symbol table
struct symtab{
	int index;
	char symbol[10];
	int address,size;
};

struct littab{
	int index;
	char literal[10];
	int add;
};

//Operation code table (Mnemonic opcode table)
struct mottab{
	char mnemonic_code[10],class[3];
	int machine_code,length;
};

struct ic{
	int first;
	char second[4];
	int third;
  char fourth[4];
	int fifth;
	char sixth[4];
	int seventh;
};

struct registers{
	char reg_name[10];
	int reg_code;
};

//referenced tables
struct mottab mtab[18];	//mnemonic opcode table
struct registers reg[4];	//registers

//to be created tables
struct symtab stab[30];	//symbol table
struct littab ltab[10];	//literal table
struct ic intermediateCode[25];	//intermediate code

int end_found = 0,start_found=0;
int LC = 0;
int PTP=0,LTP=0,STP=0;	//pool table pointer, Literal table pointer, Symbol table pointer
int ICP=0;	//intermediate code pointer
char *words[5];
int pooltab[10];

void init(struct mottab m[14],struct registers r[4]){
	//initialize machine code, class and length
	for(int i = 0;i<11;i++){
		strcpy(m[i].class,"IS");
		m[i].machine_code = i;
		m[i].length = 2;
	}

	strcpy(m[11].class,"DL");
	m[11].machine_code = 12;
	m[11].length = 1;

	strcpy(m[12].class,"DL");
	m[12].machine_code =13;
	m[12].length = 99;

	//initializes mnemonic code
	strcpy(m[0].mnemonic_code,"STOP");
	strcpy(m[1].mnemonic_code,"ADD");
	strcpy(m[2].mnemonic_code,"SUB");
	strcpy(m[3].mnemonic_code,"MULT");
	strcpy(m[4].mnemonic_code,"MOVER");
	strcpy(m[5].mnemonic_code,"MOVEM");
	strcpy(m[6].mnemonic_code,"COMP");
	strcpy(m[7].mnemonic_code,"BC");
	strcpy(m[8].mnemonic_code,"DIV");
	strcpy(m[9].mnemonic_code,"READ");
	strcpy(m[10].mnemonic_code,"PRINT");
	strcpy(m[11].mnemonic_code,"DC");
	strcpy(m[12].mnemonic_code,"DS");

	for(int i = 13 ; i < 18;i++){
		strcpy(m[i].class,"AD");	//assembler directive
		m[i].machine_code = i-12;
	}

	strcpy(m[13].mnemonic_code,"START");
	strcpy(m[14].mnemonic_code,"END");
	strcpy(m[15].mnemonic_code,"LTORG");
	strcpy(m[17].mnemonic_code,"ORIGIN");
	strcpy(m[16].mnemonic_code,"EQU");

	//Initialization of Registers
	strcpy(r[0].reg_name,"AREG");
	r[0].reg_code = 1;
	strcpy(r[1].reg_name,"BREG");
	r[1].reg_code = 2;
	strcpy(r[2].reg_name,"CREG");
	r[2].reg_code = 3;
	strcpy(r[3].reg_name,"DREG");
	r[3].reg_code = 4;
}

// checks MOT Table, returns location if found, else returns -1
int check_mottab(char *token){
	// printf("The length of the word %s is %ld\n",token,strlen(token));
	for(int i=0;i<18;i++){
		// printf("mtab[i].mnemonic = \"%s\", token =\" %s\"\n",mtab[i].mnemonic_code,token);
		if(strcmp(mtab[i].mnemonic_code,token) == 0){
			return i;
		}
	}
	return -1;
}

void set_literal_tab(int lit_id,char lit_name[20],int lit_adr){
	ltab[LTP].index = lit_id;
	strcpy(ltab[LTP].literal,lit_name);
	ltab[LTP].add = lit_adr;
	LTP++;
}

// checks registers Table, returns register code if found, else returns 0
int check_register(char a[10]){

	for(int i = 0 ;i<4;i++){
		if(strcmp(reg[i].reg_name,a) == 0){
			return reg[i].reg_code;
		}
	}
	return 0;
}

// checks symbol Table, returns location if found, else returns -1
int check_symtab(char token[10]){
	printf("words : %s\n",token);
	for(int i = 0 ;i< STP;i++){
		if(strcmp(stab[i].symbol,token)==0){
			return i;
		}
	}
	return (-1);
}

//checking functions
int isLiteral(char* curWord)
{
	int len = strlen(curWord);
	printf("\n Word : %s\n",curWord);
	printf("\nLength of Literal : %d\n",len);
	char temp;
	int i = 0,check;
	check = -1;

	if(curWord[0] == '=' && curWord[1] == '\'' && curWord[len-1] == '\'')
	{
		for(i=0;i<len-3;i++)
		{
			temp = (int)curWord[i+2];
			check = isdigit(temp);
			if(check == 0)	//not a numeric character => it is not a literal
			{
				return 0;
			}
		}

		return 1;
	}
	return 0;
}

void update_literal_table()
{
	int temp = pooltab[PTP];
	temp--;
	int i;
	for(i=temp;i<LTP;i++)
	{
		ltab[i].add = LC;
		LC = LC+1;
	}
	PTP++;
	pooltab[PTP] = LTP+1;
}

//print functions
void printSYMTAB()
{
	FILE *fptr = NULL;
	fptr = fopen("symtab.txt","w");
	int i;
	printf("\n******************** SYMBOL TABLE **********************\n");
	printf("\nSym-Id  Sym-Name      Sym-Adr    Sym-Size   \n");
	printf("\n********************************************************\n");
	for(i=0;i<STP;i++)
	{
		printf("%-8d",stab[i].index);
		printf("%-14s",stab[i].symbol);
		printf("%-11d",stab[i].address);
		printf("%-11d",stab[i].size);
		printf("\n");
		fprintf(fptr,"%d %s %d %d\n",stab[i].index,stab[i].symbol,stab[i].address,stab[i].size);
	}
	printf("\n--------------------------------------------------------\n");
	fclose(fptr);
}

void printLITTAB()
{
	FILE *fptr = NULL;
	fptr = fopen("littab.txt","w");
	int i;
	printf("\n******************** LITERAL TABLE **********\n");
	printf("\nLiteral-Id  Literal-Name      Literal-Adr    \n");
	printf("\n*********************************************\n");
	for(i=0;i<LTP;i++)
	{
		printf("%-12d",ltab[i].index);
		printf("%-18s",ltab[i].literal);
		printf("%-15d",ltab[i].add);
		printf("\n");
		fprintf(fptr,"%d %s %d\n",ltab[i].index,ltab[i].literal,ltab[i].add);
	}
	printf("\n--------------------------------------------------------\n");
	fclose(fptr);
}

void print_pooltab(){
	FILE *fptr = NULL;
	fptr = fopen("pooltab.txt","w");
	printf("\n******POOLTAB******\n");
	printf("\nCONTENT\n");
	printf("\n*******************\n");
	for(int i = 0 ; i< PTP;i++){
		fprintf(fptr,"%d\n",pooltab[i]);
		printf("%d\n",pooltab[i]);
	}
	printf("\n--------------------------------------------------------\n");
	fclose(fptr);
}

#endif /* STRUCTURES_H_ */
