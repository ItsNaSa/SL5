#include<stdio.h>

struct optab{
    char opcode[20],class[5],info[5];
    int no_operands;
};

struct symtab{
    char symname[20];
    int add,length;
};

struct littab{
    char litname[20];
    int add;
};

struct pooltab{
    char literal[50];
};

struct ic{
    char class_code[20];
    int reg_no,sr_no;
};