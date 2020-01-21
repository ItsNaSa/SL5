/*
 * mergeSort.h
 *
 *  Created on: 21-Jan-2020
 *      Author: pict
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_
#define MAX 1000

typedef struct song{
	int song_number;
	char name[25];
	double length;
}song;

void merge(song song_list[],int l,int m,int h){
    int n1 = m-l+1,n2=h-m;
    song L[n1],R[n2]; // define two temp arrays, left is L, right is R

    int i,j;
    for (i = 0; i < n1; i++)
		L[i] = song_list[l + i];
	for (j = 0; j < n2; j++)
		R[j] = song_list[m + 1+ j];

    i=j=0;
    int k=l;

    while(i<n1 && j<n2){    //merge the array to the original array while sorting
        if (L[i].length <= R[j].length){
            song_list[k] = L[i];
            i++;
        }
        else {
            song_list[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        song_list[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        song_list[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(song song_list[],int l, int h){
    if(l<h){
        int m = (l+h)/2;
        mergeSort(song_list,l,m);
        mergeSort(song_list,m+1,h);
        merge(song_list,l,m,h);
    }
}

//song list is already sorted as per length
void put_songs(song song_list[],int n_of_songs,song tapes[][MAX],int n_of_tapes){
    int j=0;
    for(int i = 0; i < n_of_songs; i++){
        tapes[i%n_of_tapes][j] = song_list[i];
        if(i==0)
            continue;
        else if(i%n_of_tapes == 0){
            j++;
        }
    }
}

#endif /* MERGESORT_H_ */
