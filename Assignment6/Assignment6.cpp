#include<iostream>
using namespace std;

typedef struct city {
    string cityname;
    int cityID;
}city;

typedef struct edge {
    int src,dest, weight;
}edge;

void print_cities(city cities[50],int V){
    cout<<"Cities in the graph :: "<<endl;
    for(int i=0;i<V;i++){
        cout<<cities[i].cityID<<". "<<cities[i].cityname<<endl;
    }
}

void print_edges(city cities[50],edge edges[50],int E){
    cout<<"The graph is as follows :: "<<endl;
    for (int i = 0; i < E; i++)
    {
        cout<<i+1<<".\t"<<cities[edges[i].src].cityname<<"\t --->> \t"<<cities[edges[i].dest].cityID<<"\t|\t"<<edges[i].weight<<endl;
    }
}

void bellman_ford(city cities[50],int V,edge edges[50],int E,int min_distance[50],int path[][2]){
    int source;
    print_cities(cities,V);
    cout<<"Enter the source to search min distance. ";
    cin>>source;
    for(int i = 0; i < V-1; i++){
        for(int j = 0; j < E; j++){
             //TODO add the code to solve bellman ford
        }
    }
}

int main(){
    city cities[50];
    edge edges[50];
    int min_distance[50] = {INT32_MAX};
    int V,E;
    cout<<"Enter number of cities :: ";
    cin>>V;
    for(int i = 0;i<V;i++){
        cout<<"Enter city name :: ";
        cin>>cities[i].cityname;
        cities[i].cityID = i;
    }
    cout<<"Enter the number of edges :: ";
    cin>>E;
    for (int i = 0; i < E; i++)
    {   
        print_cities(cities,V);
        cout<<"Enter the edge source :: ";
        cin>>edges[i].src;
        cout<<"Enter the edge destination :: ";
        cin>>edges[i].dest;
        cout<<"Enter the weight of the edge :: ";
        cin>>edges[i].weight;

        cout<<"\t\t"<<edges[i].src<<"\t --->> \t"<<edges[i].dest<<"\t|\t"<<edges[i].weight<<endl;
    }
    print_edges(cities,edges,E);
    bellman_ford(cities,V,edges,E,min_distance,path);
}
