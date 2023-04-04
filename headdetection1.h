#include <iostream>
#include<vector>
#include<fstream>
#include<map>
#include<set>
#include<string>

#define endl "\n";
using namespace std;
typedef long long ll;
void make_graph_input(string input_file,string output_file) {

	ifstream fin;
    fin.open(input_file);
    // 2 lines ????????
    ofstream fout;
    // fout.open("Users/alien/Downloads/code/vandal2/firstloop2output.txt");
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
    map<string,vector<string>> block_variables;
    int itr=0;
    int cnt=0;
    vector <string> v;
    vector <string> k;
    
    // while(getline(fin,s))
    // {


        
    //     // cout<<s<<" "<<cnt_partitions<<endl;s
	
    // 	// if(s==block[itr]) in_block=true,itr++;
    // 	if( s=="---") cnt_partitions++;
    //     if( cnt_partitions==0)
    // 	{
    //         // cout<<"val of s "<<s<<esndl;
    //         bool flag=false;
    //         cnt++;
    // 		string part="";
            
    //             int len=0;
    // 		for(auto ch:s)
    // 		{
    //             len++;
                
    //             if(ch==' ')
    // 			{
                    
    // 				if(part[0]=='B') {
    //                     flag=true;
    //                 }

    // 				part="";
    // 			}
    // 			else part+=ch;

    //             if(len==s.size() && flag){
    //                     // cout<<"part while inserting "<<part<<endl;
    //                     v.push_back(part);

    //                     // block_variables[block[itr-1]].insert(part);
    //                     // in_block=false;
    //                     cnt=0;
    //             }
                
    // 		}
            
           
    // 	}

        
        
       
    // 	if(s=="================================") cnt_partitions=0;
    //     else if ( s == "Function 0:") break;







    // }

    


       while(getline(fin,s))
    {
            // cout<<s<<" "<<cnt_partitions<<endl;s
	
    	// if(s==block[itr]) in_block=true,itr++;
    	if( s=="---") cnt_partitions++;
        if( cnt_partitions==0)
    	{
            // cout<<"val of s "<<s<<esndl;
            bool flag=false;
    		string part="";
            
                int len=0;
    		for(auto ch:s)
    		{
                len++;
                
                if(ch==' ')
    			{
                    
    				if(part[0]=='B') {
                        flag=true;
                    }

    				part="";
    			}
    			else part+=ch;

                if(len==s.size() && flag){
                        // cout<<"part while inserting "<<part<<endl;
                        v.push_back(part);

                        // block_variables[block[itr-1]].insert(part);
                        // in_block=false;
                }
                
    		}
            
           
    	}

        
        


        
        // cout<<s<<" "<<cnt_partitions<<endl;s
	
    	// if(s==block[itr]) in_block=true,itr++;
    	// if( s=="---") cnt_partitions++;
        if( cnt_partitions==1)
    	{
            // cout<<"val of s "<<s<<esndl;
            bool flag2=false;
            cnt++;
    		string part1="";
            if(cnt==3){
                int length=0;
    		for(auto chara:s)
    		{
                length++;
                
                if(chara=='[')
    			{
                    
    				if(part1 == "Successors: ") {
                        flag2=true;
                    }

    				part1="";
    			}
    			else part1+=chara;

                if(length==s.size()-1 && flag2){
                        // cout<<"part while inserting "<<part1<<endl;
                        k.push_back(part1);

                        // block_variables[block[itr-1]].insert(part);
                        // in_block=false;
                        cnt=0;
                }
                
    		}
            }
            
           
    	}

        
        
       
    	if(s=="================================") cnt_partitions=0;
        else if ( s == "Function 0:") break;







    }



    


 



    // for(auto ele:block_variables){
    //     fout<<ele.first<<" : ";
    //     for(auto var:ele.second){
    //         fout<<var<<" ";
    //     }
    //     fout<<endl;
    // }
    map<string,int> nodes;
    for(int i=0;i<v.size();i++)
    {
    	nodes[v[i]]=i;
    }
    int edges=0;
    for (int i=0; i<k.size(); i++){
    	string str="";
        for(int j=0;j<k[i].size();j++)
        {
        	if(k[i][j]==',' || k[i][j]==' ')
        	{
        		if(str!="") block_variables[v[i]].push_back(str),edges++;
        		str="";
        	}
        	else str+=k[i][j];
        }
        if(str!="") block_variables[v[i]].push_back(str),edges++;
    }
    
    fout<<v.size()<<" "<<edges<<endl;
    for(auto node:v) fout<<node<<endl;
    for(auto node:block_variables)
    {
    	for(auto ngh:node.second)
    	{
    		fout<<nodes[node.first]<<" "<<nodes[ngh]<<endl;
    	}
    }
    
	fin.close();
	fout.close();
}
