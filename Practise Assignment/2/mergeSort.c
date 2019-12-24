#include<stdio.h>
#include<string.h>
#define max 100

void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 

void merge(int arr[],int l,int m,int h){
    int n1 = m-l+1,n2=h-m;
    int L[n1],R[n2]; // define two temp arrays, left is L, right is R

    int i=0,j;
    for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j];

    printf("Array 2 is ");
    printArray(R,n2);
    i=j=0;
    int k=l;
    
    while(i<n1 && j<n2){    //merge the array to the original array while sorting
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }   
        k++;
    }

    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[],int l, int h){
    if(l<h){
        int m = (l+h)/2;
        printf("l is %d, h is %d and m is %d\n",l,h,m);
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,h);
        merge(arr,l,m,h);
    }
}

/* Driver program to test above functions */
int main() 
{ 
	int arr[] = {12, 11, 13,14,10,19,4,5,2,1}; 
	int arr_size = sizeof(arr)/sizeof(arr[0]); 


    if(arr_size<=1){
        printf("The array need not be sorted\n");
    }
	printf("Given array is \n"); 
	printArray(arr, arr_size); 

	mergeSort(arr, 0, arr_size - 1); 

	printf("\nSorted array is \n"); 
	printArray(arr, arr_size); 
	return 0; 
} 
