#include<stdio.h>
#include<string.h>
#include<ctype.h>
typedef struct UST{
    int srno;
    char symbol[100],type[20];
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

int search_idn(idn ident[70],char token[100]){
	for(int i = 0 ;i < IDN_PTR;i++){
		if(strcmp(ident[i].identifierString,token) == 0){
			return i;
		}
	}
	return -1;
}

//1 will return operators, 2 will return for '&' and 0 -> not operator
int isOperator(char ch){
    if (ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/' || ch == '%' || ch =='!' || ch == '=')
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

// if lexium is not a terminal, return 0
int create_lexium(char token[100],UST uni[1500],trn term_tab[70]){
	int indexT = -1;
	indexT = check_trn(token,term_tab);
	if (indexT == -1){
		return 0;
	}
	uni[UST_PTR].index = indexT;
	uni[UST_PTR].srno = uni[UST_PTR-1].srno + 1;
	strcpy(uni[UST_PTR].symbol,token);
	strcpy(uni[UST_PTR].type,"TRN");
	UST_PTR++;
	return 1;
}

// TODO see the issue of extra space, new line and double literal

void tokenize(UST uni_sym_tab[1500],trn terminal_table[70],idn identifier_table[50],lit literal_table[50]){
    FILE *fptr = fopen("temp.c","r");
    char temp[100];
    char ch,prev_ch='\0';
	int flag = 0;
    int i =0;
	while((ch = fgetc(fptr)) != EOF){
		printf("CURRENT CHARACTER IS \'%c\'!!!!!\t\t\t and previous character was \'%c\'!!!!!!\n",ch,prev_ch);
		if(ch == '\n' || ch == '\0'){
			prev_ch = ch;
			continue;
		}
		else if(prev_ch != ']' && ch == '.'){	// if . is used in headers 
			temp[i++] = ch;
			prev_ch = ch;
			printf("temp = %s\n",temp);
			continue;
		}	
        else if(isalpha(ch) || isdigit(ch)){	//if a number or a terminal string like int, include, etc. or an identifier
            temp[i++] = ch; //keep on going till we read all the char or integers
			prev_ch = ch;
			printf("temp = %s\n",temp);
			continue;
        }
        else if(ch == ',' || ch == ';'||ch == '\0' || ch == '\n' || ch == ' ' || ch=='\t'){	// when we reach end of line or space,
			//when the character is ',' or ';', it is a terminal, so update 
			if(ch == ',' || ch == ';' || ch == ' ' || ch == '\t'){	//if lexium ends here
				if(prev_ch == ' ' || prev_ch == '\t' || prev_ch == '\0'){	//if blank spaces or \t or \0 are continuously occuring, continue the loop
					prev_ch = ch;
					continue;
				}
				else if(ch == ';' || ch == ','){
					if(create_lexium(temp,uni_sym_tab,terminal_table) == 0){	//if it is an identifier
						//check if it is existing
						int index_idn = -1;
						index_idn = search_idn(identifier_table,temp);
						if(index_idn == -1){	//if not existing
							// Update IDENTIFIER TABLE
							strcpy(identifier_table[IDN_PTR].identifierString,temp);
							index_idn = identifier_table[IDN_PTR].index = IDN_PTR;
							IDN_PTR++;	
						}
						// Update UST
						uni_sym_tab[UST_PTR].index = index_idn;
						uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno + 1;
						strcpy(uni_sym_tab[UST_PTR].symbol,temp);
						strcpy(uni_sym_tab[UST_PTR].type,"IDN");
						UST_PTR++;
						memset(temp,0,100);
					}
					i=0;
					temp[0] = ch;
					temp[1] = '\0';
					create_lexium(temp,uni_sym_tab,terminal_table);
					printf("temp = %s\n",temp);
				}
				else{
					temp[i++] = '\0';
					printf("temp = %s\n",temp);
					i=0;
					//update if terminal
					if(create_lexium(temp,uni_sym_tab,terminal_table) == 0){	//if it is an identifier
						//check if it is existing
						int index_idn = -1;
						index_idn = search_idn(identifier_table,temp);
						if(index_idn == -1){	//if not existing
							// Update IDENTIFIER TABLE
							strcpy(identifier_table[IDN_PTR].identifierString,temp);
							index_idn = identifier_table[IDN_PTR].index = IDN_PTR;
							IDN_PTR++;	
						}
						// Update UST
						uni_sym_tab[UST_PTR].index = index_idn;
						uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno + 1;
						strcpy(uni_sym_tab[UST_PTR].symbol,temp);
						strcpy(uni_sym_tab[UST_PTR].type,"IDN");
						UST_PTR++;
						memset(temp,0,100);
					}
				}
			}
			}
        else {
			//if any of the operator is encounterd
            if(isOperator(ch) != 0){
                if(i > 0){	//if an IDN or a TRN is already there (read)
					temp[i++] = '\0';
					//update the UST
       					if(create_lexium(temp,uni_sym_tab,terminal_table) == 0){	//if it is an identifier
						//check if it is existing
						int index_idn = -1;
						index_idn = search_idn(identifier_table,temp);
						if(index_idn == -1){	//if not existing
							// Update IDENTIFIER TABLE
							strcpy(identifier_table[IDN_PTR].identifierString,temp);
							index_idn = identifier_table[IDN_PTR].index = IDN_PTR;
							IDN_PTR++;	
						}
						// Update UST
						uni_sym_tab[UST_PTR].index = index_idn;
						uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno + 1;
						strcpy(uni_sym_tab[UST_PTR].symbol,temp);
						strcpy(uni_sym_tab[UST_PTR].type,"IDN");
						UST_PTR++;
						memset(temp,0,100);
					}
					i = 0;
					memset(temp,0,100);	//clear the buffer
                }
				//if double operators are there, like &&, || ,
                if(isOperator(prev_ch) && (prev_ch == ch || (ch == '='))){
                    temp[0] = prev_ch;
                    temp[1] = ch;
                    temp[2] = '\0';
                	printf("temp = %s\n",temp);
				}
            	else{
                	temp[0] = ch;
                	temp[1] = '\0';
            		printf("temp = %s\n",temp);
				}
				create_lexium(temp,uni_sym_tab,terminal_table);
				memset(temp,0,100);
            }
            else if(ch == '\"')	//if literal is encountered
			{
				// first update the existing lexium
				temp[i++] = '\0';
				printf("temp = %s\n",temp);
                if(create_lexium(temp,uni_sym_tab,terminal_table) == 0){	//if it is an identifier
					//check if it is existing
					int index_idn = -1;
					index_idn = search_idn(identifier_table,temp);
					if(index_idn == -1){	//if not existing
						// Update IDENTIFIER TABLE
						strcpy(identifier_table[IDN_PTR].identifierString,temp);
						index_idn = identifier_table[IDN_PTR].index = IDN_PTR;
						IDN_PTR++;	
					}
					// Update UST
					uni_sym_tab[UST_PTR].index = index_idn;
					uni_sym_tab[UST_PTR].srno = uni_sym_tab[UST_PTR-1].srno + 1;
					strcpy(uni_sym_tab[UST_PTR].symbol,temp);
					strcpy(uni_sym_tab[UST_PTR].type,"IDN");
					UST_PTR++;
					memset(temp,0,100);
				}
				i = 0;				
				temp[i++]=ch;	//copy the literal into literal table
				ch = fgetc(fptr);
				while(ch != '\"'){
					temp[i++] = ch;
					ch = fgetc(fptr);
				}
				temp[i++] = ch;
				temp[i++] = '\0';	//end the copy
            	printf("temp = %s\n",temp);

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

void display(UST uni_sym_tab[1500],lit lit_tab[50],idn iden_tab[50]){
	printf("UNIFORM SYMBOL TABLE\n");
	printf("\nSr.No\tSymbol\t\tIndex\t\n");
	for (int i =0;i<UST_PTR;i++){
		printf("%d\t%s\t\t%d\t\n",uni_sym_tab[i].srno,uni_sym_tab[i].symbol,uni_sym_tab[i].index);
	}
	printf("\n\n");
	printf("LITERAL SYMBOL\nSr. no.\tSymbol\t\tIndex\t\n");
	for(int i = 0 ; i < LIT_PTR;i++){
		printf("%d\t%s\t\n",lit_tab[i].index,lit_tab[i].literalString);
	}
}