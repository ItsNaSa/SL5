#include<stdio.h>

int cost[10][10],n;
int lookup[10][64];

struct term{

int val;

int index; // to be used for finding path not used here

int ival;  // to be used for finding path not used here

};

typedef struct term aterm;

int find_min(aterm a[10], int len) {
  int i,min;
  min=a[1].val;

  for(i=2;i<=len;i++)
    if(a[i].val < min) {
			min = a[i].val;
  }
  return min;
}

// a is the source, m1 is the no. of cities (last index)
int gis(int a, int s[10], int m1, int v[10]) {
  int min,i,j,k,p,q,m,r,ind,set[10],visited[10];

  aterm x[10];
  i=a; m=m1;

  for(k=1;k<=n;k++)
  	visited[k]=v[k];

  visited[i]=1;	//mark the first node as visited (source)

  if(m==1) //if only two nodes are there
  	return(cost[i][s[1]] + cost[s[1]][1]);	//return addition

  int set_value = 0;

  for(int i = 1; i <= m1; i++) {
	  if(v[i] == 0)
  		  set_value += (1 << s[i]);
	  printf("set_value = %d and 1<<s[i] = %d\n",set_value,1<<s[i]);
  }
  printf("set_value = %d \n",set_value);

  for(ind=1;ind<=m;ind++) {
    j=s[ind];
    p=1;
    for(k=1;k<=n;k++) {
      if((k!=j) && (!visited[k])) {
	     set[p]=k;
	     p++;
	    }
    }
    int cost1;
    if(lookup[a][set_value - (1 << j)])
    	cost1 = lookup[a][set_value - (1 << j)];
    else cost1 = gis(j,set,m-1,visited);

    x[ind].val = cost[i][j] + cost1;
  }

  min=find_min(x,m);
  lookup[a][set_value] = min;
  return min;
}

 int main() {

  int city,v[10],s[10],i,j,k,min,path[10],p,index;
  int dec,done,rcount,total[10],n1;
  printf("enter no of cities:");
  scanf("%d",&n);

  for(i=1;i<=n;i++)
     for(j=1;j<=n;j++)
	 	scanf("%d",&cost[i][j]);

   printf("cost matrix is\n");

   for(i=1;i<=n;i++){
      for(j=1;j<=n;j++)
        printf("\t%d",cost[i][j]);
      printf("\n");
    }

   for(i=1;i<=n-1;i++) {
     s[i]=i+1;
     v[i]=0;
    }

    v[n]=0;

    min=gis(1,s,n-1,v);

    printf("minimum cost tour is%d\n",min);

return 0;

}
