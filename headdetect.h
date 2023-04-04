// fuml namshebaazi
#include <bits/stdc++.h>
#define endl "\n";
using namespace std;
typedef long long ll;
vector<int> adj[50];
vector<int> vis(50,0);
vector<int> heads;
vector<int> bodies;
void dfs(int n)
{
	vis[n]=1;
	for(auto ch:adj[n])
	{
		if(!vis[ch])
		{
			dfs(ch);
		}
		else
		{
			heads.push_back(ch);
			bodies.push_back(n);
		}
	}
}
void head_detect(string input_file,string output_file)
{
	ifstream fin;
    fin.open(input_file);
    ofstream fout;
    fout.open(output_file);
	int n,m;fin>>n>>m;
	vector<string> nodes;
	for(int i=0;i<n;i++)
	{
		string s;fin>>s;
		nodes.push_back(s);
		// cout<<s<<" ";
	}
	for(int i=0;i<m;i++)
	{
		int a,b;fin>>a>>b;
		adj[a].push_back(b);
		// cout<<a<<":"<<b<<" ";
	}
	dfs(0);
	fout<<"heads: "; 
	for(auto ele:heads) fout<<nodes[ele]<<" ";
	fout<<endl;
	fout<<"bodies: ";
	for(auto ele:bodies) fout<<nodes[ele]<<" ";
	fout<<endl;
}