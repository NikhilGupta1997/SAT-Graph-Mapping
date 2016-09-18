#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdio.h>

using namespace std;

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

int phind(vector<edge> G, int x, int y){
	int gsize = G.size();
	for(int i=0; i<gsize; i++){
		if(G[i].start == x && G[i].end == y)
			return 1;
	}
	return 0;
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
	vector<edge> G1;
	vector<edge> G2;
	vector<int> nodes1;
	vector<int> nodes2;
	while(!input.eof()){
		edge temp = extractNumbers(line);
		cout<<temp.start<<endl<<temp.end<<endl;

		if(temp.start==0 && temp.end==0)
		{
			flag = 1;
		}
		else
		{	
			if(flag == 0) ////// G
			{
				G1.push_back(temp);
				if(std::find(nodes1.begin(), nodes1.end(), temp.start) == nodes1.end()){
					nodes1.push_back(temp.start);
					n++;
				}
				if(std::find(nodes1.begin(), nodes1.end(), temp.end) == nodes1.end()){
					nodes1.push_back(temp.end);
					n++;
				}
			}
			else //////// G'
			{
				G2.push_back(temp);
				if(std::find(nodes2.begin(), nodes2.end(), temp.start) == nodes2.end()){
					nodes2.push_back(temp.start);
					m++;
				}
				if(std::find(nodes2.begin(), nodes2.end(), temp.end) == nodes2.end()){
					nodes2.push_back(temp.end);
					m++;
				}
			}
		}
		getline(input,line);
	}

	int no_of_vars = n*n + m*m + n*m;
	int no_of_clauses = n*n + m*m + m + 2*(n*m*(n*m-1));
	output<<"p cnf "<<no_of_vars<<" "<<no_of_clauses<<endl;

    int count = 1;
    for(int i=1; i<=n; i++){
    	for(int j=1; j<=n; j++){
    		if(phind(G1, i, j)){
    			output<<count<< " 0\n";
    		}
    		else
    			output<<"-"<<count<< " 0\n";
    		count++; 
    	}
    }
    int end_count1 = count;
    for(int i=1; i<=m; i++){
    	for(int j=1; j<=m; j++){
    		if(phind(G2, i, j)){
    			output<<to_string(count)<< " 0\n";
    		}
    		else
    			output<<"-"<<to_string(count)<< " 0\n";
    		count++; 
    	}
    }
    int end_count2 = count;
    for(int i=1; i<=m; i++){
    	for(int j=1; j<=n; j++){
    		output<<to_string(count)<<" ";
    		count++;
    	}
    	output<<"0\n";
    }
    for(int i=1; i<=n; i++){
    	for(int j=1; j<=m; j++){
    		for(int k=1; k<=n; k++){
    			for(int l=1; l<=m; l++){
    				if(i==k && j==l)
    					continue;
    				else if(j>l)
    					continue;
    				else if(j==l && i>k)
    					continue;
    				else{
    					output<<"-"<<to_string((j-1)*n+i+end_count2)<<" -"<<to_string((l-1)*n+k+end_count2)<<" -"<<to_string((i-1)*n+k)<<" "<<to_string((j-1)*m+l+end_count1)<< " 0\n";
    					output<<"-"<<to_string((j-1)*n+i+end_count2)<<" -"<<to_string((l-1)*n+k+end_count2)<<" -"<<to_string((k-1)*n+i)<<" "<<to_string((l-1)*m+j+end_count1)<< " 0\n";
    					output<<"-"<<to_string((j-1)*n+i+end_count2)<<" -"<<to_string((l-1)*n+k+end_count2)<<" -"<<to_string((j-1)*m+l+end_count1)<<" "<<to_string((i-1)*n+k)<< " 0\n";
    					output<<"-"<<to_string((j-1)*n+i+end_count2)<<" -"<<to_string((l-1)*n+k+end_count2)<<" -"<<to_string((l-1)*m+j+end_count1)<<" "<<to_string((k-1)*n+i)<< " 0\n";
    				}
    			}
    		}
    	}
    }
    output.close();
    return 0;
}
