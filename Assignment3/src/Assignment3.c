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

int main(int argc, char *argv[]) {
	load_littab();
	load_pooltab();
	load_symtab();

	create_machine_code();

	return EXIT_SUCCESS;
}
