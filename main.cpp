#include <bits/stdc++.h>
// #include<fstream>
// #include "/Users/alien/Desktop/whileoptimizer/headdetect.h"
// #include "/Users/alien/Desktop/whileoptimizer/lowerbound.h"
// #include "/Users/alien/Desktop/whileoptimizer/stackvariable.h"
// #include "/Users/alien/Desktop/whileoptimizer/upperbound.h"
// #include "/Users/alien/Desktop/whileoptimizer/headdetection1.h"
#include "headdetect.h"
#include "lowerbound.h"
#include "stackvariable.h"
#include "upperbound.h"
#include "headdetection1.h"
#define endl "\n";
using namespace std;
typedef long long ll;

int convert(string hexVal)
{
    int len = hexVal.size();
 
    // Initializing base value to 1, i.e 16^0
    int base = 1;
 
    int dec_val = 0;
 
    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;
 
            // incrementing base by power
            base = base * 16;
        }
 
        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F'||hexVal[i] >= 'a' && hexVal[i] <= 'f') {
            dec_val += (int(hexVal[i]) - 'a'+10) * base;
 
            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}

int main() {

    system("solc --bin-runtime code.sol | tail -n 1 > code.hex");
    system("python3 bin/decompile code.hex > disasm.txt");
    // system("cd dow")

	// string disasm_input_file="/Users/alien/Desktop/whileoptimizer/disasm.txt";
	// string graph_input_file="/Users/alien/Desktop/whileoptimizer/input_file.txt";
	// string graph_output_file="/Users/alien/Desktop/whileoptimizer/graph_output_file.txt";
    string disasm_input_file="disasm.txt";
	string graph_input_file="input_file.txt";
	string graph_output_file="graph_output_file.txt";


	make_graph_input(disasm_input_file,graph_input_file);
	head_detect(graph_input_file,graph_output_file);

	ifstream fin2;
    fin2.open(graph_output_file);

    string k = "";
    int rnt = 0;
    vector<string> heads;
    vector<string> tails;

    if (!fin2.is_open())
    {
        cout << "Error3";
    }
        bool flag = false;
        bool flag2 = false;
        bool next=false;
    while (getline(fin2, k))
    {

        rnt++;
        string part = "";
        if (rnt == 1)
        {
            int len = 0;
            for (auto ch : k)
            {
                // cout<<"vla of ch "<<ch<<endl;
                len++;

                if (ch ==' ')
                {

                    if (part[0] == 'h')
                    {
                        flag = true;
                        part = "";

                    }
                    else if(flag){
                        next=true;
                    }

                }
                else
                    part += ch;
                // cout<<"part in el se "<<part<<endl;

                if (next && flag || (len==k.size()))
                {
                    // cout<<"val of part "<<part<<endl;
                    heads.push_back("Block " +part);
                    next=false;
                    part="";
                    // flag=false;
                    // rnt = 0;
                }
            }
        }

        if (rnt == 2)
        {
            int len = 0;
            for (auto ch : k)
            {
                // cout<<"vla of ch "<<ch<<endl;
                len++;

                if (ch ==' ')
                {

                    if (part[0] == 'b')
                    {
                        flag2 = true;
                        part = "";

                    }
                    else if(flag2){
                        next=true;
                    }

                }
                else
                    part += ch;
                // cout<<"part in el se "<<part<<endl;

                if (next && flag2 || (len==k.size()))
                {
                    // cout<<"val of part "<<part<<endl;
                    tails.push_back("Block " +part);
                    next=false;
                    part="";
                    // flag=false;
                    // rnt = 0;
                }
            }
        }

    }
    // block.push_back("abc");




    // for ( auto it : heads){
    //     cout << it << endl;
    // }

    fin2.close();

	string lower_bound_output_file="/Users/alien/Desktop/whileoptimizer/lower_bound.txt";
	lower_bound(disasm_input_file,lower_bound_output_file, heads);
	
	string upper_bound_output_file="/Users/alien/Desktop/whileoptimizer/upper_bound.txt";
	upper_bound(disasm_input_file,upper_bound_output_file, heads);
	
	string stack_variable_output_file="/Users/alien/Desktop/whileoptimizer/stack_variable.txt";
	find_stack_variable(disasm_input_file,stack_variable_output_file,tails);

    // ifstream fin3;
    // fin3.open(upper_bound_output_file);

    // map < string , vector<string> > m;


    // if (!fin3.is_open())
    // {
    //     cout << "Error4" << endl;
    // }

    // string up = "";
    // int i =0;

    // while (getline(fin3,up)){
    //     bool flag1 = false;
    //     string part = "";
    //     for (auto ch: up){
    //         int len =0;
    //         len ++;
    //         if (ch = ' '){

    //             if (part == ":"){
    //                 flag = true;
    //                 part = "";
    //             }

    //             else part += ch;
                
    //         }

    //         if (flag1 && len == up.size()){
                
    //             m[heads[i]].push_back(part);
    //             i++;


    //         }

    //     }

    // }

    // fin3.close();



    ifstream fin3;
    fin3.open(upper_bound_output_file);

    map < string , int > m;
    // vector<string> tails={"Block 0x85" , "Block 0xa2" };
    vector<int> upper;
    // cout << tails[1]<<endl;
    



    if (!fin3.is_open())
    {
        cout << "Error4" << endl;
    }

    string up = "";
    int iup=0;
    

    while (getline(fin3,up)){
        // int i=0;
        bool flag1 = false;
        string part = "";
        int len=0;
        for (auto ch: up){
            // int len =0;
            len ++;
            if (ch ==' '){

                // auto x = part.size();

                if (part[part.size()-1] == ':'){
                    flag1 = true;
                    part = "";
                }

                
                
            }
            else part += ch;
            // cout<< part<<endl;

            

            if (flag1 && len == up.size()){
                
                m[heads[iup]] = convert(part);
                // cout << tails[i];
                
                // cout << "a";
                
                


            }

        }
        iup++;
        // cout << i<< endl;

        // cout<< part<< endl;
        // cout << convert (part) << endl;

        // cout << flag1;
        


    }

    

    // for (auto it = m.begin(); it!= m.end();it++){
    //     int j=0;
    //     cout << it->first << ": " << it->second;

        
    //     // j++;
    //     // string value;
    //     // for ( auto value: (*it).second){
    //     //     cout << value;
    //     // }

    //     cout << endl;
    //     // for (int i =0; i < m[tails[j]].size(); i++){
    //     //     cout << tails[j] << " "<< (*it).second;

    //     // }

    //     // cout << (*it).second << endl;

    // }

    fin3.close();

    ifstream fin4;
    fin4.open(lower_bound_output_file);

     map < string , int > m2;
    // vector<string> tails={"tails 0x85" , "tails 0xa2" };
    vector<int> lower;

     if (!fin4.is_open())
    {
        cout << "Error5" << endl;
    }

    string low = "";
    int klow=0;

    while (getline(fin4,low)){
        // int i=0;
        bool flag1 = false;
        string part = "";
        int len=0;
        for (auto ch: low){
            // int len =0;
            len ++;
            if (ch ==' '){

                // auto x = part.size();

                if (part[part.size()-1] == ':'){
                    flag1 = true;
                    part = "";
                }

                
                
            }
            else part += ch;
            // cout<< part<<endl;

            

            if (flag1 && len == low.size()){
                
                m2[heads[klow]] = (convert(part));
                // cout << tails[i];
                
                // cout << "a";
                
                


            }

        }
        klow++;
        // cout << i<< endl;

        // cout<< part<< endl;
        // cout << convert (part) << endl;

        // cout << flag1;
        


    }

    

    // for (auto it = m2.begin(); it!= m2.end();it++){
    //     int j=0;
    //     cout << it->first << ": " << it-> second;

        
    //     // j++;
    //     // string value;
    //     // for ( auto value: (*it).second){
    //     //     cout << value;
    //     // }

    //     cout << endl;
    //     // for (int i =0; i < m[tails[j]].size(); i++){
    //     //     cout << tails[j] << " "<< (*it).second;

    //     // }

    //     // cout << (*it).second << endl;

    // }
    fin4.close();

 int diff[m.size()];
    map < int , vector<string> > md;
    map<string,int> loop_size;

    for (int i=0; i< m.size();i++){

        diff[i] = m[heads[i]] - m2[heads[i]];

        // cout << diff[i] << " " <<endl;

        md[diff[i]].push_back(heads[i]);
        
        loop_size[heads[i]] = diff[i];



    }

    //  for (auto it = md.begin(); it!= md.end();it++){
        
    //     cout << it->first << ": " ;

        
    
        
    //     for ( auto value: (*it).second){
    //         cout << value << " ";
    //     }

    //     cout << endl;
    //  }

    // cout << endl;
    
    ifstream fin5;
    fin5.open(stack_variable_output_file);
    
    int n=tails.size();
    vector<bool> grp_fusible((1<<n)+5,false);
    vector<vector<string>> stack_variables(n+5);
    
    string str="";
    int line=0;
    while (getline(fin5,str))
    {
    	string s="",block="";
    	int flag=0;
    	for(int i=0;i<str.size();i++)
    	{
    		if(str[i]==' ')
    		{
    			if(flag && s!="") stack_variables[line].push_back(s);
    			else block=s;
    			s="";
    		}
    		else if(str[i]==':')
    		{
    			s="";
    			flag=1;
    		}
    		else s+=str[i];
    	}
    	if(flag && s!="") stack_variables[line].push_back(s);
    	line++;
    }
    
    for(int i=1;i<(1<<n);i++)
    {
        if(__builtin_popcount(i) <= 1) continue;
    	set<int> check;
    	int ans=1;
    	for(int j=0;j<n;j++)
    	{
    		if((1<<j) & i) check.insert(loop_size[heads[j]]);
    	}
    	map<string,set<string>> stackVariables_to_block;
    	if(check.size() == 1)
    	{
    		for(int j=0;j<n;j++)
	    	{
	    		if((1<<j) & i)
	    		{
	    			for(auto var:stack_variables[j])
	    			{
	    				stackVariables_to_block[var].insert(heads[j]);
	    			}
	    		}
	    	}
	    	for(auto ele:stackVariables_to_block)
	    	{
	    		// cout<<ele.first<<": ";
	    		// for(auto var:ele.second) cout<<var<<" ";
	    		if(ele.second.size()>1) ans=0;
	    	}
    	} 
    	else ans=0;
    	
    	if(ans)
    	{
    		cout<<"Block ";
    		for(int j=0;j<n;j++)
	    	{
	    		if((1<<j) & i) cout<<j+1<<", ";
	    	}
	    	cout<<"are fusible";
	    	cout<<endl;
    	}
    }
    
    
	fin5.close();
	
	return 0;
}