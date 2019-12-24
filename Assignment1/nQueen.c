#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define n 100

int col_pos[n] = {0};

void display_solution(int number_of_rows){
    for(int i = 0; i< number_of_rows;i++){
        for (int j = 0; j < number_of_rows; j++)
        {
            if(col_pos[i] == j){
                printf("Q ");
            }
            else{
            	printf("- ");
        	}
        }
        printf("\n");
    }
    
}

int place(int number_of_queen,int current_column){
    for (int i = 0; i < number_of_queen; i++)
    {
        if (col_pos[i] == current_column || abs(col_pos[i] - current_column) == abs(i-number_of_queen))
        {
            return 0;
        }
        
    }
    return 1;
    
}

int n_queen(int number_of_queen,int number_of_rows){
    for (int i = 0; i < number_of_rows; i++)        //traverses columns
    {
        if (place(number_of_queen,i))
        {
            col_pos[number_of_queen] = i;
            if(number_of_queen == number_of_rows - 1){
                display_solution(number_of_rows);
                printf("\n\n"); 
            }
            else
            {
                n_queen(number_of_queen+1,number_of_rows);
            }
            
        }
        
    }
    
}

int main(void){
    int number;
    printf("Enter number of queen's :: ");
    scanf("%d",&number);
    n_queen(0,number);
}
