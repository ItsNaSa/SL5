#include<stdio.h>
#include <string.h>
typedef struct UST{
    int srno;
    char symbol[100];
    int index;
}UST;

typedef struct literal
{
    char literalString[100];
    int index;
}lit;

typedef struct identifiers{
    char identifierString[20];
    int index;
}idn;

typedef struct terminals
{
    char terminalString[20];
    int index;
}trn;

int LIT_PTR = 0;
int IDN_PTR = 0;
int UST_PTR = 0;

void load_trn(trn terminal_table[70]){
   int index1,i=0;
   char token[20];
    FILE *fptr = fopen("terminaltable.txt","r");
    printf("Reading file\n");
    while (!feof(fptr))
    {
        fscanf(fptr,"%s %d",token,&index1);
		terminal_table[i].index = index1;
        strcpy(terminal_table[i].terminalString,token);
        i++;
    }
    printf("Value of i = %d\n",i);        
    fclose(fptr);
}

int check_trn(char token[10],trn terminal_table[70]){
	for (int i = 0; i < 64; i++)
	{
		if(strcmp(token,terminal_table[i].terminalString)==0){
			return i;
		}
		else
		{
			continue;
		}
	}
}

//1 will return operators, 2 will return for '&' and 0 -> not operator
int isOperator(char ch){
    if (ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/' || ch == "%" || ch =='!' || ch == '=')
    {
        return 2;
    }
    else if(ch == '#' || ch =='<' || ch == '>' || ch =='^' || ch == '&' || ch == '|')
        return 3;
	else if(ch == '(' || ch ==')' || ch == '{' || ch == '}' ||ch == '[' ||ch == ']' ||ch =='\\')
		return 4;
	else 
        return 0;
}

int create_lexium(char token[100],UST uni[1500],trn term_tab[70]){
	int indexT = -1;
	indexT = check_trn(token,term_tab);
	if (indexT == -1){
		return 0;
	}
	uni[UST_PTR].index = indexT;
	uni[UST_PTR].srno = uni[UST_PTR-1].srno + 1;
	strcpy(uni[UST_PTR].symbol,token);
	UST_PTR++;
	return 1;
}

void tokenize(UST uni_sym_tab[1500],trn terminal_table[70],idn identifier_table[50],lit literal_table[50]){
    FILE *fptr = fopen("temp.c","r");
    char temp[100];
    char ch,prev_ch='\0';
	int flag = 0;
    int i =0;
    //TODO handle '.' in stdio.h
	//TODO check for identifier
	while((ch = fgetc(fptr)) != EOF){
		// if(prev_ch != ']')	// if . is used as access 
		// 	flag =1;
        if(isalpha(ch) || isdigit(ch)){	//if a number or a terminal string like int, include, etc. or an identifier
            temp[i++] = ch; //keep on going till we read all the char or integers
			continue;
        }
        else if(ch == '\0' || ch == '\n' || ch == ' ' || ch == "," || ch == ';'){	// when we reach end of line or space,
																					// we have read an identifier or a terminal
            temp[i++] = '\0';
            i = 0;
			if(create_lexium(temp,uni_sym_tab,terminal_table) == 0){	//if an identifier
				//update identifier table
				identifier_table[IDN_PTR].index = IDN_PTR+1;
				strcpy(identifier_table[IDN_PTR].identifierString,temp);

				//update the UST
				uni_sym_tab[UST_PTR].index = IDN_PTR+1;
				strcpy(uni_sym_tab[UST_PTR].symbol,temp);
				uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno+1;
				//increment pointer
				IDN_PTR++;
				UST_PTR++;
			}
			memset(temp,0,100);	
			//else if it is a terminal, it will be updated

			//when the character is ',' or ';', it is a terminal, so update 
			if(ch == ',' || ch == ';'){
				temp[0] = ch;
                temp[1] = '\0';
				create_lexium(temp,uni_sym_tab,terminal_table);
				memset(temp,0,100);
			}
        }
        else {
			//if any of the special character is encounterd
            if(isOperator(ch) != 0){
                if(i > 0){	//if am IDN or a TRN is already there (read)
					temp[i++] = '\0';
					//update the UST
                    if(create_lexium(temp,uni_sym_tab,terminal_table) == 0){	//if an identifier
						//update identifier table
						identifier_table[IDN_PTR].index = IDN_PTR+1;
						strcpy(identifier_table[IDN_PTR].identifierString,temp);
						//update the UST
						uni_sym_tab[UST_PTR].index = IDN_PTR+1;
						strcpy(uni_sym_tab[UST_PTR].symbol,temp);
						uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno+1;
						//increment pointer
						IDN_PTR++;
						UST_PTR++;
					}
					i = 0;
					memset(temp,0,100);	//clear the buffer
                }
				//if double operators are there, like &&, || ,
                if(isOperator(prev_ch) && (prev_ch == ch || (ch == "="))){
                    temp[0] = prev_ch;
                    temp[1] = ch;
                    temp[2] = '\0';
                }
            	else{
                	temp[0] = ch;
                	temp[1] = '\0';
            	}
				create_lexium(temp,uni_sym_tab,terminal_table);
				memset(temp,0,100);
            }
            else if(ch == '\"')	//if literal is encountered
			{
				temp[i++] = '\0';
                create_lexium(temp,uni_sym_tab,terminal_table);
				i = 0;
				memset(temp,0,100);
				
				temp[i++]=ch;	//copy the literal into literal table
				while(ch != '\"'){
					ch = fgetc(fptr);
					temp[i++] = ch;
				}
				temp[i++] = '\0';	//end the copy

				//update literal table
				literal_table[LIT_PTR].index = LIT_PTR+1;
				strcpy(literal_table[LIT_PTR].literalString,temp);
				
				//update Uniform Symbol Table
				uni_sym_tab[UST_PTR].index = LIT_PTR+1;	//index of literal in UST
				strcpy(uni_sym_tab[UST_PTR].symbol,temp);	//copy the literal in UST
				uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno+1;	//update sr. no.

				LIT_PTR++;
				UST_PTR++;
				//literal complete
			}

        }
        prev_ch = ch;
    }
    fclose(fptr);
}