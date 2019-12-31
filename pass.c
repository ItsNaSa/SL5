#include<stdio.h>
#include<string.h>

struct symtab{
	char symbol[5];
	int add,length;
};

struct littab{
	char literal[10];
	int add;
};

char pooltab[20];

struct mottab{
	char mnemonic_code[5],class[2];
	int machine_code,length;
};

struct pottab{
	char pseudo_opcode[6],class[2];
	int inter_machine_code;
};

struct ic{
	char class_code[20];
	int reg_no,sr_no;
};

struct table{
	char label[10],mnemonic_code[5],op1[10],op2[10];
};

void pass(struct table t)
{
	symtab s[15];
	int sym_ptr=0,max_sym=0;
	//1
	int LC=0,PTP=1,LTP=1,STP=1,RC=0;
	pooltab[1]=1;

	//2
	if(strcmp(t.label)!=0)
	{
		//a
		if(strcmp(t.label,NULL)!=0)
		{
			sym_ptr=search_symtab(t.label);
			if(sym_ptr!=-1)
			{
				s[sym_ptr].add=LC;
				s[sym_ptr].length=t.op1;
			}
			else
			{
				s[max_sym].label=t.label;
				s[max_sym].add=LC;
				max_sym++;
			}
		}
	}
	//3
	else
	{

	}
}
void disp(char *line)
{
	int count=0;
	char* token = strtok(line, "\t"); 
	struct table t;
    while (token != NULL) { 
        printf("\n%s", token);
        count++;

        if(strcmp(token,"-")!=0 && count==1)
	        strcpy(t.label,token);
	    if(strcmp(token,"-")==0)
	    	count--;

        if(count==2)
        	strcpy(t.mnemonic_code,token);

        if(count==3)
        	strcpy(t.op1,token);

        if(count==4)
        	strcpy(t.op2,token);

        token = strtok(NULL, "\t"); 
    } 
    printf("word count::%d",count);
    pass(t);
}

void init()
{
	struct mottab m[13];
	struct pottab p[5];
	int i;

	strcpy(m[0].mnemonic_code,"STOP");
	strcpy(m[1].mnemonic_code,"ADD");
	strcpy(m[2].mnemonic_code,"SUB");
	strcpy(m[3].mnemonic_code,"MULT");
	strcpy(m[4].mnemonic_code,"MOVER");
	strcpy(m[5].mnemonic_code,"MOVEM");
	strcpy(m[6].mnemonic_code,"COMP");
	strcpy(m[7].mnemonic_code,"BC");
	strcpy(m[8].mnemonic_code,"DIV");
	strcpy(m[9].mnemonic_code,"READ");
	strcpy(m[10].mnemonic_code,"PRINT");

	strcpy(m[11].mnemonic_code,"DC");
	m[11].machine_code=01;
	strcpy(m[11].class,"DL");
	m[11].length=1;

	strcpy(m[12].mnemonic_code,"DS");
	m[12].machine_code=02;
	strcpy(m[12].class,"DL");
	m[12].length=1;

	for(i=0;i<10;i++)
		m[i].machine_code=i;

	for(i=0;i<10;i++)
		m[i].length=2;

	for(i=0;i<10;i++)
		m[i].length=2;

	strcpy(p[0].pseudo_opcode,"START");
	strcpy(p[1].pseudo_opcode,"END");
	strcpy(p[2].pseudo_opcode,"LTORG");
	strcpy(p[3].pseudo_opcode,"ORIGIN");
	strcpy(p[4].pseudo_opcode,"EQU");

	for(i=0;i<5;i++)
	{
		p[i].inter_machine_code=i;
		strcpy(p[i].class,"AD");
	}
}
int main()
{
	init();
	FILE *fp;
   char *line = NULL;
   size_t len = 0;
   ssize_t nread;
	fp=fopen("code.txt","r");
	
	if(fp==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		while ((nread = getline(&line, &len, fp)) != -1) {
           printf("\n\nRetrieved line of length %zu:", nread);
           //fwrite(line, nread, 1, stdout);
           disp(line);
       }

       free(line);
		fclose(fp);
		printf("\n\nData read successfully!!");
	}
	return 0;
}