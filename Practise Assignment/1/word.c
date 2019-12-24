#include<stdio.h>
#include<string.h>
#define MAX 1024

int main(){
    char newLine[20];
    char ch;
    FILE *afile,*bfile;
    char oriFileName[40],newFileName[40];
    printf("Enter the file name to read from :: ");
    scanf("%s",oriFileName);
    printf("Enter the file name to write to :: ");
    scanf("%s",newFileName);
    
    afile=fopen(oriFileName,"r");
    bfile=fopen(newFileName,"w");

    while(!feof(afile)){
        fscanf(afile,"%s",newLine);
        int temp = strlen(newLine);
        if(newLine[temp-1] == '.'){
        	newLine[temp-1]='\0';
        }
        printf("LINE IS %s",newLine);
        
   	    fprintf(bfile,"%s\n",newLine);
   	    for(int i = 0;i<20;i++){
   	    	newLine[i] = '\0';
   	    }
            	
    }
    
    
}
