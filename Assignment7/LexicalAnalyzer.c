#include<stdio.h>

typedef struct UST{
    char symbol[10];
    int index;
}UST;

typedef struct literal
{
    char literalString[50];
    int index;
}lit;

typedef struct identifiers{
    char identifierString[20];
    int index;
}idn;

typedef struct terminals
{
    char terminalString[10];
    int index;
}trm;

int main(){
    trm terminals[]
    load_trm();
}