#include<stdio.h>
#include<string.h>
#define MAX 1024

int main(){
    char newFileName[40];
    char word[30]="\0";
    char search[30];
    printf("Enter the word file name :: ");
    scanf("%s",newFileName);
    printf("Enter the word to read :: ");
    scanf("%s",search);

    FILE *fp;
    fp = fopen(newFileName,"r");
    while(!feof(fp)){
        fscanf(fp,"%s\n",word);
        if(strcmp(word,search)==0){
            printf("WORD %s found\n",search);
        }
        else{
            for (int i = 0; i < 30; i++)
            {
                word[i]='\0';
            }
            continue;
        }
    }
}