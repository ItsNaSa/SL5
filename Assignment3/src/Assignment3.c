/*
 ============================================================================
 Name        : Assignment3.c
 Author      : 33140
 Version     :
 Copyright   : NO NOTICE!!!! ;P
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int main(void) {
	load_littab();
	load_pooltab();
	load_symtab();

	return EXIT_SUCCESS;
}
