#include<stdio.h>
#include <string.h>
#include "struct.h"

int main(){
    trn terminals[70];
	UST uni_sym_tab[1500];
	idn identifier_table[50];
	lit literal_table[50];
    printf("LOADING TERMINALS\n");
    load_trn(terminals);
	create_lexium(uni_sym_tab,terminals,identifier_table,literal_table);
}