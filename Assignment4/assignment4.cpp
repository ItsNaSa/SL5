#include <iostream>
#define MAX 200
using namespace std;

int n = 0;

struct numbers{
    int min;
    int max;
};

//function to find the min and max of the given array
void findMinMax(int array[],int start,int end,struct numbers *a,int *pass1){
    struct numbers temp1,temp2;
    
    cout<<"\n**===================================================================**"<<endl;
    cout<<"Pass number :: "<< (*pass1)++ <<"\nStart of the array :: "<< start <<"\nEnd of the array :: "<< end <<endl;	//printing the pass and start and end of the divided array
    cout<<"\n--------------------------------------------------------------------"<<endl;
    cout<<"Array :: ";	//print the divided array
    for(int i = 0; i < n;i++){
        if(i >= start && i <= end){
            cout<<array[i]<<"\t";
        }
        else 
            cout<<"\t";
    }
    cout<<endl;
    cout<<"--------------------------------------------------------------------"<<endl;

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
        cout<<"--------------------------------------------------------------------"<<endl;
        cout<<"\t\t\tMERGING from start = "<<start<<" to end ="<<end<<endl;
        cout<<"Array :: ";
        for(int i = 0; i < n;i++){
            if(i >= start && i <= end){
                cout<<array[i]<<"\t";
            }
            else 
                cout<<"\t";
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
    cout<<"\nLocal min :: "<<a->min<<" --- Local max :: "<<a->max<<endl;
    cout<<"--------------------------------------------------------------------"<<endl;
    cout<<"**===================================================================**\n\n";
    return;
}

int main(void)
{
    struct numbers ans;
    int array[MAX];
    int pass_number = 0;
    
    //accepting number of elements of the array
    cout<<"Enter the number of elements : "<<endl;
    scanf("%d",&n);	//n is global array
    cin>>n;
    //accepting the array
    cout<<"Enter the elements :: \n";
    for(int i = 0;i < n; i++){
        cin>>array[i];
    }
	//print the array
    cout<<"Array :: ");
    for (int i = 0; i < n; i++){
        cout<<"%d\t",array[i]);
        cout<<A
    }
    cout<<endl;
    
    //pass the array to find the min and max
    findMinMax(array,0,n-1,&ans,&pass_number);
    //print the max and min of the total
    cout<<"\n\nGlobal maxima :: %d ---- Global minima :: %d\n\n",ans.max,ans.min);
    return 0;
}
