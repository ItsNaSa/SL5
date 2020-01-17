//Assignment 4 - Min Max using Divide and Conquer algorithm
//ROLL NO - 33140
//Batch name - L9

#include <stdio.h>
#define MAX 200

int n = 0;

//structure of the numbers
struct numbers{
    int min;
    int max;
};

//function to find the min and max of the given array
void findMinMax(int array[],int start,int end,struct numbers *a,int *pass1){
    struct numbers temp1,temp2;
    
    printf("\n**===================================================================**\n");
    printf("Pass number :: %d\nStart of the array :: %d\nEnd of the array :: %d\n",(*pass1)++,start,end);	//printing the pass and start and end of the divided array
    printf("\n--------------------------------------------------------------------\n");
    printf("Array :: ");	//print the divided array
    for(int i = 0; i < n;i++){
        if(i >= start && i <= end){
            printf("%d\t",array[i]);
        }
        else 
            printf("\t");
    }
    printf("\n");
    printf("--------------------------------------------------------------------\n");

	//if only one element (smallest sub-case), the same is min and max
    if (start == end) {
        a->min = a->max = array[start];
    }
    else if(start == (end-1)){	//two elements, second smallest sub-case, compare which one is min or max
        if(array[end] > array[start]){
            a->max = array[end];
            a->min = array[start];
        }
        else{
            a->max = array[start];
            a->min = array[end];
        }
    }
    //else if more than 2 elements, divide till we get smallest sub-case
    else if (start<end){
        int mid = (start+end)/2;	//divide on the mid
        findMinMax(array,start,mid,&temp1,pass1);	//left half
        findMinMax(array,mid+1,end,&temp2,pass1);	//right half
        
        //after out of recursion, from the merged solution, check for min and max from those two halves....
        printf("--------------------------------------------------------------------\n");
        printf("\t\t\tMERGING from start = %d to end = %d\n",start,end);
        printf("Array :: ");
        for(int i = 0; i < n;i++){
            if(i >= start && i <= end){
                printf("%d\t",array[i]);
            }
            else 
                printf("\t");
        }
		//put the combined halves' answer into the structure for passing to previous recursion 
        if(temp1.min > temp2.min){
            a->min = temp2.min;
        }
        else{
            a->min = temp1.min;
        }

        if(temp1.max > temp2.max){
            a->max = temp1.max;
        }
        else{
            a->max = temp2.max;
        }
    }
    //print the min and max of the merged part0
    printf("\nLocal min :: %d --- Local max :: %d\n",a->min,a->max);
    printf("--------------------------------------------------------------------\n");
    printf("**===================================================================**\n\n");
    return;
}

int main(void)
{
    struct numbers ans;
    int array[MAX];
    int pass_number = 0;
    
    //accepting number of elements of the array
    printf("Enter the number of elements : ");
    scanf("%d",&n);	//n is global array
    
    //accepting the array
    printf("Enter the elements :: \n");
    for(int i = 0;i < n; i++){
        scanf("%d",&array[i]);
    }
	//print the array
    printf("Array :: ");
    for (int i = 0; i < n; i++){
        printf("%d\t",array[i]);
    }
    printf("\n");
    
    //pass the array to find the min and max
    findMinMax(array,0,n-1,&ans,&pass_number);
    //print the max and min of the total
    printf("\n\nGlobal maxima :: %d ---- Global minima :: %d\n\n",ans.max,ans.min);
    return 0;
}
