#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <climits>

using namespace std;

#define inf 9999999

struct node
{
	pair<int,int> *ar;
	int vertex;
	node(int n, int vertex)
	{
		// create a new map
		ar = new pair<int,int>[n];
		this->vertex = vertex;

		for (int i=0 ; i < n ; i++)
		{
			if (i==vertex)
				ar[i].first =i,ar[i].second=0;
			// if other initialize to inf
			else 
				ar[i].first = i,ar[i].second=inf;
		}
	}
	node()
	{
		ar = NULL,vertex=-1;
	}
};

struct graph
{
	vector<vector<int> > edges;
	node *ar;
	int n;

	graph(int n)
	{
		edges.resize(n);
		ar = new node[n];	
		this->n = n;
		for (int i=0 ; i < n ; i++)
		{
			// explicit constructor call
			ar[i] = node(n,i);			
		}
	}

	void add_edge(int u , int v, int w)
	{
		ar[u].ar[v].second=w; 
		ar[v].ar[u].second=w;

		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	// print vectors for each
	//
	void print()
	{
		for (int i=0; i < n ; i++)
		{
			// print the current vector;
			
			cout<<"Vertex "<<i<<endl;
			for (int j=0 ; j<n ; j++)
				cout<<ar[i].ar[j].first<<" "<<ar[i].ar[j].second<<endl;
		}
	}
};

bool broadcast(graph &g, int from , int to)
{
	node &from_node = g.ar[from];
	node &to_node = g.ar[to];
	
	bool flag = false;
	int dist_to_broadcast = to_node.ar[from].second;

	for (int i=0 ; i < g.n; i++)
	{
		if (i== to)
			continue;

		if (to_node.ar[i].second > from_node.ar[i].second + dist_to_broadcast)
		{
			to_node.ar[i].second = from_node.ar[i].second + dist_to_broadcast;
			flag = true;
		}
	}

	return flag;
}

int main()
{
	int num_vertex,num_edges,u,v,w;
	cout<<"Enter number of vertices : ";
	cin>>num_vertex;

	cout<<"Enter number of edges: ";
	cin>>num_edges;

	graph g(num_vertex);
	
	for (int i=0; i < num_edges; i++)
	{
		cout<<"Enter edge triplet(u,v,w): ";
		cin>>u>>v>>w;

		g.add_edge(u,v,w);
	}
	

	// now start broadcasting 
	
	bool update_required =false;
	
	do
	{
		cout<<"Updating vectors--"<<endl;
		update_required =false;
		// broadcast in cycles 
		for (int i=0; i<num_vertex; i++)
		{
			// broadcast vector from node i
			
			for(int j=0 ; j<g.edges[i].size() ; j++)
			{
				bool did_update = broadcast(g,i,g.edges[i][j]);	
				update_required = update_required | did_update;
			}
		}
	}
	while(update_required);

	// print the distance vectors
	g.print();
}
