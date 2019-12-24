#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

int main(){
	string filename;
	string newLine;
	int choice;
	fstream file;
	cout<<"1. New Input"<<endl;
	cin>>choice;
	switch(choice){
		case 1:
			cout<<"Enter the file name :: ";
			cin>>filename;
	
			file.open(filename,ios::in);
			if(!file.is_open()){
			
			}
			else{
				cout<<"Enter a new line. Enter # to end the input.";
				cin.getline(newLine,MAX);
				if(strcmp(newLine,'#')!=0){
					file<<newLine;
				}
				else{
					cout<<"End of the input!"<<endl;
				}
			}	
			break;

	}
	 
}
