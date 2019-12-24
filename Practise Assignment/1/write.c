#include<stdio.h>
#include<string.h>
#define MAX 1024

int main(){
	char filename[40];
	char newLine[MAX];
    char ch;
    int i = 0;

	int choice;
	FILE *afile;
	printf("Enter the file name :: ");
	scanf("%s",filename);
	
			afile=fopen(filename,"w");
			if(afile==NULL){
                printf("Error opening the file\n");
                return -1;
			}
			else{
				while(1){
					scanf("%c",&ch);
                    if(ch=='*')
                        break;
                    else{
                        newLine[i++]=ch;
                    }
				}
                newLine[i++]='\0';
                printf("End of input!");
                fprintf(afile,"%s\n",newLine);
			}
            fclose(afile);	

}
	 

