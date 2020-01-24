//Assignment 3
//Roll no - 33121
//Batch - L9


//headers
#include<stdio.h>
#include<string.h>

//structures
struct symtab{
	char symbol[10];
	int add,length;
};

struct littab{
	char literal[10];
	int add;
};

char pooltab[20];

struct ic{
	char class_code[20],C[5],sym_lit[5],str[10];
	int constant1,constant2,machine_code,lc;
};

int LC=0,PTP=0,LTP=0,STP=0,RC=0,ic_ptr=0;
struct ic i_counter[20];
struct symtab s[20];
struct littab l[20];

//funtion to tokenise lines
void disp(char *line)
{
	printf("hii");
	int count=0;
	char* token = strtok(line, "\t"); 

	char buff[20];

	//till more token exits
    while (token != NULL) {
    	strcpy(buff,token); 
    	if(count==0)
    		sscanf(buff,"%d",&i_counter[ic_ptr].lc);
    	
    	else if(count==1)
    		sscanf(buff,"%s",i_counter[ic_ptr].class_code);
    	
    	else if(count==2)
    		sscanf(buff,"%d",&i_counter[ic_ptr].machine_code);

    	else if(count==3)
    		sscanf(buff,"%s",i_counter[ic_ptr].C);
    	
    	else if(count==4)
    	{
    		if(buff[0]=='\'')
    			sscanf(buff,"%s",i_counter[ic_ptr].str);
    		else	
    			sscanf(buff,"%d",&i_counter[ic_ptr].constant1);
    	}

    	else if(count==5)
    		sscanf(buff,"%s",i_counter[ic_ptr].sym_lit);

    	else if(count==6)
    		sscanf(buff,"%d",&i_counter[ic_ptr].constant2);
    
        count++;
        strcpy(buff,"NULL");
        printf("%s\n",token);
        token = strtok(NULL, "\t");
    } 
    ic_ptr++;
}

//Function to preprocess intermediate code to remove brackets and comma
void pre_process()
{
	FILE *f=NULL,*f1=NULL;
	char ch;
	f=fopen("Copy of output.txt","r");
	f1=fopen("intermediate_code.txt","w");
	if(f==NULL || f1==NULL)
	{
		printf("\nError in opening file!!");
	}
	else
	{
		while((ch=fgetc(f))!=EOF)
		{
			if(ch==',')		//if , found print \t in file
			{
				fprintf(f1,"\t");
			}
			else if(ch!='(' && ch!=')')		//if ( or ) this found print the character in file
			{
				fprintf(f1, "%c",ch);
			}
		}
	}
	fclose(f);
	fclose(f1);
}
//copy tables from file to structure
void copy_from_file()
{
	char *line = NULL;
	size_t len = 0;
    ssize_t nread;
    int counter=0,i=0;


    //copy symtab from file symtab structure
	FILE *fptr=NULL;
	fptr=fopen("symtab.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		 while(fscanf(fptr,"%s %d %d",s[i].symbol,&s[i].add,&s[i].length)!=EOF)
		 {
		 	printf("%s\t%d\t%d\n",s[i].symbol,s[i].add,s[i].length);
		 	STP=i;
		 	i++;
		 }	
   	}
	fclose(fptr);
	i=0;

	//copy littab from file to structure
	fptr=fopen("littab.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		 while(fscanf(fptr,"%s %d",l[i].literal,&l[i].add)!=EOF)
		 {
		 	printf("%s\t%d\n",l[i].literal,l[i].add);
		 	LTP=i;
		 	i++;
		 }	
   	}
	fclose(fptr);
	i=0;

	//copy pooltab from file to structure
	fptr=fopen("pooltab.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		 while(fscanf(fptr,"%d",&pooltab[i])!=EOF)
		 {
		 	printf("%d\n",pooltab[i]);
		 	PTP=i;
		 	i++;
		 }	
   	}
	fclose(fptr);

	i=0;
	int j;

	//pre process the file
	pre_process();

	//copy intermediate code from file to structure
	fptr=fopen("intermediate_code.txt","r");

	if(fptr==NULL)
	{
		printf("\nFailed to open file to read!!");
	}
	else
	{
		while ((nread = getline(&line, &len, fptr)) != -1) 
		{
			counter++;
           printf("\n\nRetrieved line %d of length %zu:",counter, nread);
           disp(line);
        }

        //print whole structure of intermediate code
        for(int j=0;j<ic_ptr;j++)
        {
        	printf("\n%d %s %d %s %d %s %d",i_counter[j].lc,i_counter[j].class_code,i_counter[j].machine_code,i_counter[j].C,i_counter[j].constant1,i_counter[j].sym_lit,i_counter[j].constant2);
        }
   	}
	fclose(fptr);
}

//function to return address of a symbol
int search_symtab(int c)
{
	return s[c-1].add;
}

//function to return address of a literal
int search_littab(int c)
{
	return l[c-1].add;
}

//pass 2
void pass2()
{
	int i,constant2;
	FILE *f=NULL;

	//open file to write
	f=fopen("pass2_op.txt","w");
	if(f==NULL)
	{
		printf("\nError in opening file!!");
	}
	else
	{
		//till all instructions are processed
		for(i=1;i<ic_ptr;i++)
		{
			//if class code is DL
			if(strcmp(i_counter[i].class_code,"DL")==0)
			{
				//if DS is mnemonic code
				if(i_counter[i].machine_code==2)
				{
					fprintf(f,"%d\n%d\n",i_counter[i].lc,i_counter[i].lc+1);
				}
				else
				{
					fprintf(f,"%d\t%s\n",i_counter[i].lc,i_counter[i].str);
				}
			}

			//if END or LTORG found
			else if(strcmp(i_counter[i].class_code,"AD")==0 && (i_counter[i].machine_code==2 || i_counter[i].machine_code==3))
			{
				fprintf(f,"%d",i_counter[i].lc);
				int c=i_counter[i].constant1;

				//for LTORG print only LC
				if(i_counter[i].machine_code==3)
					fprintf(f,"\t%s\n",l[c-1].literal);

				//for END print literals
				else
				{
					int p=pooltab[PTP];

					printf("\np-1::%d  LTP:%d",p-1,LTP);
					while((p-1)<=LTP)
					{
						fprintf(f, "\t%s\n",l[p-1].literal);
						p++;
					}
				}
			}

			//for IS statements
			else if(strcmp(i_counter[i].class_code,"AD")!=0)
			{
				fprintf(f,"%d+%d",i_counter[i].lc,i_counter[i].machine_code);

				//if register or constant is found
				if(strcmp(i_counter[i].C,"R")==0 || strcmp(i_counter[i].C,"C")==0)
					fprintf(f,"\t%d",i_counter[i].constant1);

				//if symbol is found
				if(strcmp(i_counter[i].sym_lit,"S")==0)
				{
					constant2=search_symtab(i_counter[i].constant2);
					fprintf(f,"\t%d",constant2);
				}

				//if literal is found
				else if(strcmp(i_counter[i].sym_lit,"L")==0)
				{
					constant2=search_littab(i_counter[i].constant2);
					fprintf(f,"\t%d",constant2);
				}
				fprintf(f,"\n");
			}
		}
	}
}

//Main function
int main()
{
	//copy tables from file to structures
	copy_from_file();

	//process main file
	pass2();
	return 0;
}