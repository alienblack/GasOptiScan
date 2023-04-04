#include <bits/stdc++.h>
#define endl "\n";
using namespace std;
typedef long long ll;
void find_stack_variable(string input_file,string output_file,vector<string> block){
    ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ifstream fin;
    fin.open(input_file);
    ofstream fout;
    fout.open(output_file);
    if(!fin.is_open())
    {
    	cout<<"Error1";
    	return;
    }
    if(!fout.is_open())
    {
    	cout<<"Error2";
    	return;
    }
    string s="";
    bool in_block=false;
    int cnt_partitions=0;
    // vector<string> block={"Block 0x85","Block 0xa2"};
    map<string,set<string>> block_variables;
    int itr=0;
    while(getline(fin,s))
    {
    	if(s==block[itr]) in_block=true,itr++;
    	if(in_block && s=="---") cnt_partitions++;
    	if(in_block && cnt_partitions==3)
    	{
    		string part="";
    		for(auto ch:s)
    		{


    			if(ch==' ')
    			{
    				if(part[0]=='S') {
						block_variables[block[itr-1]].insert(part);
    				    
					}
					part = "";
					
    			}
    			else part+=ch;

    		}
    		if(part[0]=='S') {
				block_variables[block[itr-1]].insert(part);
				// cout << part << " ";
			}
			
    	}
		
    	if(s=="================================") in_block=false,cnt_partitions=0;
    }
    for(auto ele:block)
    {
    	fout<<ele<<": ";
    	for(auto variables:block_variables[ele])
    	{
    		fout<<variables<<" ";
    	}
    	fout<<endl;
    } 
	fin.close();
	fout.close();
}