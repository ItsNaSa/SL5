#include<iostream>
using namespace std;

class tsp{
	// always will be a square matrix
    private:
		int adjacencyMatrix[50][50];
    	int vertices;
		int edges;
	public:
		tsp(){
			vertices = 0;
		}
	
		tsp(int vertices,int edges){
			this->vertices = vertices;
			this->edges = edges;
			// accept the edges
			for(int i = 0 ; i< vertices ;i++){
				for (int j = 0; j < vertices; j++){
					if(i == j){
						adjacencyMatrix[i][j]=0;
					}
					else
						adjacencyMatrix[i][j] = -1;
				}
			}
			for (int i = 0; i < edges; i++){
				int src,dest;
				cout<<"Enter source :: ";
				cin>>src;
				cout<<"Enter destination :: ";
				cin>>dest;
				cout<<"Enter distance between "<<src<<" ---->>>> "<<dest<<" :: ";
				cin>>adjacencyMatrix[src][dest];
			}
		}

		void display(){
			cout<<"The adjacency matrix is :: "<<endl;
			for (int i = 0; i < vertices; i++) {
				for (int j = 0; j < vertices; j++) {
					cout<<adjacencyMatrix[i][j]<<"\t";
				}
				cout<<endl;
			}	
		}

		// TODO add travelling logic
		void travel(int source){
			if(this->vertices == 2){
				
			}
		}
};

int main(){
	int vertices,edges,source;
	cout<<"Enter vertices :: ";
	cin>>vertices;
	cout<<"Enter edges :: ";
	cin>>edges;
	tsp t(vertices,edges);
	t.display();
	cout<<"Enter the start point of the salesman (between 0 to "<<vertices-1<<") :: ";
	cin>>source;
	t.travel(source);
}