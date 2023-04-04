#include <bits/stdc++.h>
#define endl "\n";
using namespace std;
typedef long long ll;
void upper_bound(string input_file,string output_file, vector<string> block){
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

// vector<int> block={1,2,3,4,5}
// block[0]->1 
// block[1]=2
// block[2]=3

    // vector<string> block={"Block 0x7b","Block 0x98"};

    // mp["string"]=>value.. ( mp["Block 0x7b"]-> 0x100)  ( result ..)
    map<string,string> block_variables;
    int itr=0;
    int cnt=0;
    while(getline(fin,s))
    {
	
    	if(s==block[itr]) in_block=true,itr++;
    	if(in_block && s=="---") cnt_partitions++;
        if(in_block && cnt_partitions==2)
    	{
            bool flag=false;
            cnt++;
    		string part="";
            if(cnt==3){
                int len=0;
    		for(auto ch:s)
    		{
                len++;
                
                if(ch==' ')
    			{
                    
    				if(part[0]=='P') {
                        flag=true;
                    }

    				part="";
    			}
    			else part+=ch;

                if(len==s.size() && flag){
                        // cout<<part<<endl;
                        block_variables[block[itr-1]] =(part);
                        in_block=false;
                        cnt=0;
                }
                
    		}
            }
           
    	}
        
       
    	if(s=="================================") in_block=false,cnt_partitions=0;
    }
    // for(auto ele:block_variables){
    //     fout<<ele.first<<" : ";
    //     for(auto var:ele.second){
    //         fout<<var<<" ";
    //     }
    //     fout<<endl;
    // }

    for (int i=0; i < block.size(); i++){
      fout << block[i]<<" : " << block_variables[block[i]] << endl;
    }

    

    

    
    
	fin.close();
	fout.close();
}