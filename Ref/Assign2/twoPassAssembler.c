#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//Mnemonic Table Structure
typedef struct mnemonicTable
{
	char mnemonicCode[20];
	char machineCode[5];
	char class[5];
	int length;
	int noOfOperands;
}mnemonicTable;

//Symbol Table Structure
typedef struct symbolTable
{
	int sym_id;
	char sym_name[25];
	int sym_adr;
	char size[10];
	char type;
}symbolTable;

//Literal Table Structure
typedef struct literalTable
{
	int lit_id;
	char lit_name[20];
	int lit_adr;
}literalTable;

//global declarations
mnemonicTable MOT[20];
symbolTable SYMTAB[20];
literalTable LITTAB[20];
int POOLTAB[10];
int STP,LTP,LC,PTP;
char *word[5];

//function to set MOT Table entries
void setMOT(int index,char mnemonicCode[20],char* machineCode,char class[5],int length,int noOfOperands)
{
	strcpy(MOT[index].mnemonicCode,mnemonicCode);
	strcpy(MOT[index].machineCode,machineCode);
	strcpy(MOT[index].class,class);
	MOT[index].length = length;
	MOT[index].noOfOperands = noOfOperands;
}

//function to set Symbol Table entries
void setSYMTAB(int sym_id,char* sym_name,int sym_adr,char* size,char type)
{
	SYMTAB[STP].sym_id = sym_id;
	strcpy(SYMTAB[STP].sym_name,sym_name);
	SYMTAB[STP].sym_adr = sym_adr;
	strcpy(SYMTAB[STP].size,size);
	SYMTAB[STP].type = type;
	STP++; 
}

//function to set Literal Table entries
void setLITTAB(int lit_id,char lit_name[20],int lit_adr)
{
	LITTAB[LTP].lit_id = lit_id;
	strcpy(LITTAB[LTP].lit_name,lit_name);
	LITTAB[LTP].lit_adr = lit_adr;
	LTP++;
}

//function to create standard MOT table
void createMOT()
{
	setMOT(0,"STOP","00","IS",2,0);
	setMOT(1,"ADD","01","IS",2,2);
	setMOT(2,"SUB","02","IS",2,2);
	setMOT(3,"MULT","03","IS",2,2);
	setMOT(4,"MOVER","04","IS",2,2);
	setMOT(5,"MOVEM","05","IS",2,2);
	setMOT(6,"COMP","06","IS",2,2);
	setMOT(7,"BC","07","IS",2,2);
	setMOT(8,"DIV","08","IS",2,2);
	setMOT(9,"READ","09","IS",2,1);
	setMOT(10,"PRINT","10","IS",2,1);
	setMOT(11,"DC","01","DL",2,1);
	setMOT(12,"DS","02","DL",2,1);
	setMOT(13,"START","01","AD",2,1);
	setMOT(14,"END","02","AD",2,0);
	setMOT(15,"LTORG","03","AD",2,0);
	setMOT(16,"ORIGIN","04","AD",2,1);
	setMOT(17,"EQU","05","AD",2,1);
} 

//checking functions
int isLiteral(char* curWord)
{		
	int len = strlen(curWord);
	printf("\nLit : %s\n",curWord);
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
			if(check == 0)
			{
				return 0;
			}	
		}
		
		return 1;
	}
	return 0;	
}

int isRegister(char* curWord1)
{
	if((strcmp(curWord1,"AREG")==0) || (strcmp(curWord1,"BREG")==0) || (strcmp(curWord1,"CREG")==0))
	{
		return 1;
	}
	return 0;
}

//search functions
int searchMOT(char curWord1[10])
{
	int i = 0;
	printf("%s",curWord1);
	while(i<18)
	{
		//printf("%s\t",MOT[i].mnemonicCode);
		if(strcmp(curWord1,MOT[i].mnemonicCode) == 0)
		{
			return i+1;
		}
		i++;
	}
	printf("\nNot in present in MOT\n");
	return 0;
}

int searchSYMTAB(char* temp)
{	
	int i;
	printf("%s",temp);
	for(i=0;i<STP;i++)
	{
		if(strcmp(SYMTAB[i].sym_name,temp) == 0)
		{
			return i+1;
		}
	}
	return 0;
}

//print functions
void printSYMTAB()
{
	int i;
	printf("\n******************** SYMBOL TABLE **********************\n");
	printf("\nSym-Id  Sym-Name      Sym-Adr    Sym-Size   Sym-Type\n");
	printf("\n********************************************************\n");
	for(i=0;i<STP;i++)
	{
		printf("%-8d",SYMTAB[i].sym_id);
		printf("%-14s",SYMTAB[i].sym_name);
		printf("%-11d",SYMTAB[i].sym_adr);
		printf("%-11s",SYMTAB[i].size);
		printf("%-8c",SYMTAB[i].type);
		printf("\n");
	}
	printf("\n--------------------------------------------------------\n");
}

void printLITTAB()
{
	int i;
	printf("\n******************** LITERAL TABLE **********\n");
	printf("\nLiteral-Id  Literal-Name      Literal-Adr    \n");
	printf("\n*********************************************\n");
	for(i=0;i<LTP;i++)
	{
		printf("%-12d",LITTAB[i].lit_id);
		printf("%-18s",LITTAB[i].lit_name);
		printf("%-15d",LITTAB[i].lit_adr);
		printf("\n");
	}
	printf("\n--------------------------------------------------------\n");
}

//utility functions
void updateLiteralTable()
{
	int pooltab = POOLTAB[PTP];
	pooltab--;
	int i;
	for(i=pooltab;i<LTP;i++)
	{
		LITTAB[i].lit_adr = LC;
		LC = LC+1;
	}
	PTP++;
	POOLTAB[PTP] = LTP+1;
}

//function to generate Intermediate Code
int generateIC(int noOfTokens)
{
	//printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	printf("\nNo of Tokens : %d\n",noOfTokens);
	FILE* fptr1 = NULL;
	fptr1 = fopen("IC.txt","a");
	char* mnemonicCode;
	int curWord = 0;
	int check = -1;
	int flag = 0;
	int temp = 0;
	int label_index = -1;
	int symbol_index = -1;
	char machine_code[10];
	int noOfOperands;
	int regCode = -1;
	int i;
	check = searchMOT(word[0]);
	//printf("%d",check);
	if(check == 0)	//label is not in the MOT table
	{
		check = searchSYMTAB(word[0]);
		if(check > 0)	//if the symbol is present in the symbol table
		{	
			printf("\nI am label in symbol table\n");	
			label_index = check-1;
			SYMTAB[check - 1].sym_adr = LC;
			//length = operand 1
		}
		else
		{
			printf("\nI am label not in symbol table\n");
			setSYMTAB(STP+1,word[0],LC,"0",'L');
		}
		check = searchMOT(word[1]);
		flag = 1;
	}
	
	if(flag == 0)
	{
		mnemonicCode = word[0];
	}
	else if(flag == 1)
	{
		mnemonicCode = word[1];
	}	
	
	check--;
	printf("\nI am mnemonic code\n");
	
	if(strcmp(mnemonicCode,"LTORG")==0)
	{
		printf("\nLTORG\n");
		//update address in symbol table
		updateLiteralTable();
		fprintf(fptr1,"(AD 03)\n");
	}
	else if(strcmp(mnemonicCode,"START")==0)
	{
		printf("\nSTART\n");
		LC  = atoi(word[flag+1]);
		fprintf(fptr1,"(AD 01)(C %d)\n",LC);
	}
	else if(strcmp(mnemonicCode,"ORIGIN")==0)
	{
		//handle arithmetic ops later
		printf("\nORIGIN\n");
		LC = SYMTAB[searchSYMTAB(word[flag+1])-1].sym_adr;
		fprintf(fptr1,"(AD 04)(C %d)\n",LC); 
	}
	else if(strcmp(mnemonicCode,"EQU")==0)
	{
		printf("\nEQU\n");
		SYMTAB[searchSYMTAB(word[0])-1].sym_adr = SYMTAB[searchSYMTAB(word[2])-1].sym_adr;
		fprintf(fptr1,"(AD 05)\n");
	}
	else if(strcmp(MOT[check].class,"DL")==0)
	{
		printf("\nDL\n");
		if(strcmp(mnemonicCode,"DS")==0)
		{
			printf("\nDS\n");
			temp = atoi(word[flag+1]);
			LC = LC+temp;
			strcpy(SYMTAB[label_index].size,word[flag+1]); 
			fprintf(fptr1,"(DL 02)(C %d)\n",temp);
		}
		else if(strcmp(mnemonicCode,"DC")==0)
		{
			printf("\nDC\n");
			LC = LC+1;
			strcpy(SYMTAB[label_index].size,word[flag+1]);
			fprintf(fptr1,"(DL 01)(C %s)\n",word[flag+1]);
		}	
	}
	else if(strcmp(MOT[check].class,"IS")==0)
	{
		printf("\nIs\n");
		noOfOperands = noOfTokens - (flag+1);
		printf("\nFlag : %d\n",flag);
		printf("\nno of operands: %d\n",noOfOperands);
		strcpy(machine_code,MOT[check].machineCode);
		fprintf(fptr1,"(IS %s)",machine_code);
		for(i=1;i<=noOfOperands;i++)
		{
			printf("\nOPernad : %d\n",i);
			if(isLiteral(word[flag+i]))
			{
				setLITTAB(LTP+1,word[flag+i],0);
				if(LTP<10)
				{
					fprintf(fptr1,"(L 0%d)",LTP);
				}
				else
				{
					fprintf(fptr1,"(L %d)",LTP);
				}	
			}
			else if(isRegister(word[flag+i]))
			{
				if(strcmp(word[flag+i],"AREG") == 0)
				{
					fprintf(fptr1,"(R 01)");
				}
				else if(strcmp(word[flag+i],"BREG") == 0)
				{
					fprintf(fptr1,"(R 02)");
				}
				else if(strcmp(word[flag+i],"CREG") == 0)
				{
					fprintf(fptr1,"(R 03)");
				}	
			}
			else 
			{
				symbol_index = searchSYMTAB(word[flag+i]);
				if(symbol_index == 0)
				{
					setSYMTAB(STP+1,word[flag+i],0,"0",'S');
					symbol_index = STP;
				}
				if(symbol_index<10)
				{
					fprintf(fptr1,"(S 0%d)",symbol_index);
				}
				else
				{
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


int main()
{
	createMOT();

	printf("\n%s\n",MOT[13].mnemonicCode);

	STP = 0;
	LTP = 0;	
	PTP = 0;
	LC = 0;
	POOLTAB[0] = 1;
	char str[50];
	char temp;
	int iterator = 0;
	int i = 0;
	int count = 0;
	int check = -1;
	int flag = 0;
	
	FILE* fptr2 = NULL;
	fptr2 = fopen("IC.txt","w");
	fclose(fptr2);
	
	FILE* fptr1 = NULL;
	fptr1 = fopen("input.txt","r");
	temp = fgetc(fptr1);
	while(!feof(fptr1))
	{	
		iterator = 0;
		while(temp != '\n')
		{
			str[iterator] = temp;
			iterator++;
			temp = fgetc(fptr1);
		}	
		str[iterator] = '\0';
		printf("%s\n",str);
		i=0;
		word[i] = strtok(str," ");
		while(word[i] != NULL)
		{
			i++;
			word[i] = strtok(NULL," ");
		}
		temp = fgetc(fptr1);
		generateIC(i);	
	}		
	fclose(fptr1);						
}
