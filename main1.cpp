#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
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

int main(int argc, char *argv[]){
	ifstream input(argv[1]);
	ofstream output;
	output.open(argv[2]);
	string line;
	int n = 0;
	int m = 0;
	int flag = 0;
	getline(input,line);

	while(!input.eof()){
		edge temp = extractNumbers(line);

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
		getline(input,line);
	}

	int matrix[m][n];
	int G1_in;
	int G2_in;
	int G1_out;
	int G2_out;
	int G1_index;
	int G2_index;
	int zero_count = 0;

	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			G1_in = G1.nodelist[j]->indeg;
			G2_in = G2.nodelist[i]->indeg;
			G1_out = G1.nodelist[j]->outdeg;
			G2_out = G2.nodelist[i]->outdeg;
			if(G2_in>G1_in || G2_out>G1_out){
				matrix[i][j] = 0;
				zero_count++;
			}
			else	
				matrix[i][j] = 1;
		}
	}

	int no_of_vars = n*n + m*m + n*m;
	int no_of_clauses = n*n + m*m + m + 2*((n*m-zero_count)*(n*m-1-zero_count)) + zero_count;
	// output<<"p cnf "<<no_of_vars<<" "<<no_of_clauses<<endl;
    int count = 1;

    for(int i=1; i<=m; i++){
    	for(int j=1; j<=n; j++){
    		output<<to_string(count)<<" ";
    		count++;
    	}
    	output<<"0\n";
    }

	for(int i=1; i<=m; i++){
    	for(int j=1; j<=n; j++){
    		if(matrix[i-1][j-1]==0){
    			output<<"-"<<to_string((i-1)*n+j)<< " 0\n";
    		}
    	}
    }

    for(int i=0; i<n; i++){
    	for(int j=0; j<m; j++){
    		for(int k=0; k<n; k++){
    			for(int l=0; l<m; l++){
    				if(i==k && j==l)
    					continue;
    				else if(j>l)
    					continue;
    				else if(j==l && i>k)
    					continue;
    				else if(matrix[j][i] == 0 || matrix[l][k] == 0)
    					continue;
    				else{
    					if(G1.findedge(G1.nodelist[i]->index,G1.nodelist[k]->index) && !G2.findedge(G2.nodelist[j]->index,G2.nodelist[l]->index))
	    					output<<"-"<<to_string((j)*n+i+1)<<" -"<<to_string((l)*n+k+1)<<" 0\n";
	    				if(G1.findedge(G1.nodelist[k]->index,G1.nodelist[i]->index) && !G2.findedge(G2.nodelist[l]->index,G2.nodelist[j]->index))	
	    					output<<"-"<<to_string((j)*n+i+1)<<" -"<<to_string((l)*n+k+1)<<" 0\n";
						if(G2.findedge(G2.nodelist[j]->index,G2.nodelist[l]->index) && !G1.findedge(G1.nodelist[i]->index,G1.nodelist[k]->index))
	    					output<<"-"<<to_string((j)*n+i+1)<<" -"<<to_string((l)*n+k+1)<<" 0\n";
	    				if(G2.findedge(G2.nodelist[l]->index,G2.nodelist[j]->index) && !G1.findedge(G1.nodelist[k]->index,G1.nodelist[i]->index))
	    					output<<"-"<<to_string((j)*n+i+1)<<" -"<<to_string((l)*n+k+1)<<" 0\n";
    				}
    			}
    		}
    	}
    }
    output.close();
    return 0;
}
