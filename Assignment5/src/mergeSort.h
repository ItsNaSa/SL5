/*
 * mergeSort.h
 *
 *  Created on: 21-Jan-2020
 *      Author: pict
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_
#define MAX 100
using namespace std;

typedef struct song{
	int song_number;
	char name[25];
	double length;
}song;

int number_of_songs_each_tape[MAX] = {0};
int minRetrievalTime[MAX] = {0};

//merges as per the length of the songs
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
        if(i==0){
            //nothing to do here
        }
        else if(i%n_of_tapes == 0){
            j++;
        }
        tapes[i%n_of_tapes][j] = song_list[i];
        number_of_songs_each_tape[i%n_of_tapes]++;
    }
}

void show_tapes(int n_of_songs,song tapes[][MAX],int n_of_tapes){
    int j=0;
    int MRT = 0;
    for(int i = 0; i < n_of_tapes;i++){
        MRT = 0;
        cout<<"\nSong in tape "<<i+1<<" :: ";
        for(int j = 0;j < number_of_songs_each_tape[i];j++){
            cout<<"("<<tapes[i][j].name<<" "<<tapes[i][j].length<<") ";
            for(int k = 0;k <= j;k++){
                MRT+=tapes[i][k].length;
            }
        }

        cout<<" || MRT :: "<<MRT<<" || Average Retrieval Time :: "<<MRT/number_of_songs_each_tape[i]<<endl;
        minRetrievalTime[i] = MRT;
        cout<<endl;
    }
}

#endif /* MERGESORT_H_ */
