#include<iostream>
#include <string.h>
using namespace std;

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

void create_lexium(UST uni_sym_tab[1500],trn terminal_table[70],idn identifier_table[50],lit literal_table[50]){
    FILE *fptr = fopen("temp.c","r");
    char temp[100];
    fclose(fptr);
}
