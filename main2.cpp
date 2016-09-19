#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

#define max 65536

using namespace std;

struct node
	{
		int index;
		int indeg;
		int outdeg;
		node(int a)
		{
			index = a;
			indeg = 0;
			outdeg = 0;
		}
	};

class Graph
{
public:
	
	vector<node*> nodelist;
	vector<node*> *adjlist;

	Graph()
	{
		adjlist = new vector<node*>[max];
	}

	node* findnode(int a)
	{
		int nsize = nodelist.size();
		int i;
		for (i=0; i<nsize; i++)
		{
			if (nodelist[i]->index==a)
				return nodelist[i];
		}
		return NULL; ///// return nsize if node does not exist
	}

	void addnode(int a)
	{
		if (findnode(a)==NULL)
		{
			node* newnode = new node(a);
			nodelist.push_back(newnode);
		}
	}

	void addEdge(int u, int v)
	{
		adjlist[u].push_back(findnode(v));
		findnode(u)->outdeg++;
		findnode(v)->indeg++;
	}

	bool findedge(int u, int v)
	{
		int usize = adjlist[u].size();
		for (int i=0; i<usize; i++)
		{
			if (adjlist[u][i]->index == v)
				return true;
		}
		return false;
	}
}G1, G2;

struct edge{
	int start;
	int end;
};

edge extractNumbers(string str){
	edge v;
	string current="";
	int extint;
	int flag = 0;
	int strsize = str.size();
	for (int i=0;i<strsize+1;i++)
	{
		if (isdigit(str[i]))
			current+=str[i];
		else if(current.size() > 0)
		{
			extint = stoi(current);
			if(flag == 0){
				v.start = (extint);
				flag = 1;
			}
			else
				v.end = extint;
			current="";
		}
	}
	return v;
}

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}

int main(int argc, char *argv[]){
    ifstream input(argv[1]);
	ifstream graph(argv[2]);
	ofstream output;
	output.open(argv[3]);
	string line, nodes;
	getline(input,line);
	getline(input,line);
	getline(graph,nodes);

	int n=0,m=0,flag=0;

	vector<string> matrix = split(line, ' ');

	while(!graph.eof()){
		edge temp = extractNumbers(nodes);

		if(temp.start==0 && temp.end==0)
		{
			flag = 1;
		}
		else
		{	
			if(flag == 0) ////// G
			{
				if(G1.findnode(temp.start) == NULL){
					n++;
					G1.addnode(temp.start);
				}
				if(G1.findnode(temp.end) == NULL){
					n++;
					G1.addnode(temp.end);
				}
				G1.addEdge(temp.start, temp.end);
			}
			else //////// G'
			{
				if(G2.findnode(temp.start) == NULL){
					m++;
					G2.addnode(temp.start);
				}
				if(G2.findnode(temp.end) == NULL){
					m++;
					G2.addnode(temp.end);
				}
				G2.addEdge(temp.start, temp.end);
			}
		}
		getline(graph,nodes);
	}

	int size = matrix.size();
	int n_size = G1.nodelist.size();
	int m_val, n_val;

	for(int i=0; i<size; i++){
		if(matrix[i][0]!='-' && matrix[i][0]!='0'){
			m_val = (i+1)/n_size+1;
			n_val = (i+1)%n_size;
			if(n_val == 0){
				m_val = m_val-1;
				n_val = n_size;
			}
			cout<<m_val<<" "<<n_val<<endl;
		}
	}

    return 0;
}
