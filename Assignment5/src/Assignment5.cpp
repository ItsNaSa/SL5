//============================================================================
// Name        : Assignment5.cpp
// Author      : 33140
// Version     :
// Copyright   : NO NOTICE!!!! ;P
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "mergeSort.h"	//structure is defined in the header
#define MAX 100
using namespace std;

int main() {
	song tapes[MAX][MAX];	//1000 tapes each containing 1000 songs
	song songs[MAX];
	int n_of_tapes = 0;
	int n_of_songs = 0;
	cout<<"Enter number of tapes to be used :: ";
	cin>>n_of_tapes;
	cout<<"Enter number of songs :: ";
	cin>>n_of_songs;

	for(int i = 0; i < n_of_songs; i++){
		// cout<<"Enter name of the song number "<<i+1<<" :: ";
		// cin>>songs[i].name;
		cout<<"Enter length of song number "<<i+1<<" :: ";
		cin>>songs[i].length;
		songs[i].song_number = i+1;
	}

	mergeSort(songs,0,n_of_songs-1);
	put_songs(songs,n_of_songs,tapes,n_of_tapes);
	show_tapes(n_of_songs,tapes,n_of_tapes);
	return 0;
}
