#include<stdio.h>
#include "structures.h"
int main(){
	init(mtab,reg);
	int loc;
	loc = check_mottab("MOVER");
	printf("The location of MOVER is %d\n",loc);
}
