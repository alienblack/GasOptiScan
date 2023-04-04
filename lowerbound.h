#include <bits/stdc++.h>
#define endl "\n";
using namespace std;
typedef long long ll;
void lower_bound(string input_file, string output_file, vector<string> block)
{
    ifstream fin;
    fin.open(input_file);
    // 2 lines ????????
    ofstream fout;
    fout.open(output_file);
    if (!fin.is_open())
    {
        cout << "Error1";
        return;
    }
    if (!fout.is_open())
    {
        cout << "Error2";
        return;
    }
    string s = "";
    bool in_block = false;
    int cnt_partitions = 0;

    // vector<int> block={1,2,3,4,5}
    // block[0]->1
    // block[1]=2
    // block[2]=3

    // vector<string> block={"V29","V30"};
    // vector<string> block={"Block 0x7b", "kfkldjf"};

    // mp["string"]=>value.. ( mp["Block 0x7b"]-> 0x100)  ( result ..)
    int itr = 0;
    int cnt = 0;
    string prvblock = "";
    bool endblock = false;
    bool emptblock = false;

    while (getline(fin, s))
    {
        if (endblock && emptblock)
        {
            if (s == block[0])
            {
                break;
            }
            // cout<<"both :"<<s<<endl;
            prvblock = s;

            emptblock = false;
            endblock = false;
        }

        if (s.empty() && endblock)
        {
            emptblock = true;
        }

        if (s == "================================")
        {
            endblock = true;
        }
    }
    // cout<<""<<endl;
    fin.clear();
    fin.seekg(0);

    int partition = 0;
    bool inblock = false;
    // vector<string> desiredblock={};
    map<string, string> block_variables;
    int idx = 0;
    string secondlast = "";
    string firstlast = "";
    string arr[block.size()+70];
    while (getline(fin, s))
    {
        // cout<<s<<endl;
        if (s == prvblock)
            inblock = true;

        if (inblock)
        {

            for (int i = 0; i < block.size(); i++)
            {
                if (partition == 3 && s != "---")
                {
                    // cout << s;
                    // secondlast=firstlast;
                    // firstlast=s;
                    arr[i] = arr[i + 1];

                    arr[i + 1] = s;

                    // cout << arr[i]<< endl;

                    // cout<<"val of s :"<<s<<endl;
                    // cout<<"firstlast inside "<<firstlast<<endl;
                    // cout<<"and secondlast "<<secondlast<<endl;
                }
            }

            if (s == "---")
                partition++;
            if (partition > 3)
                break;
        }
    }

    for (int j = 0; j < block.size(); j++)
    {
        int space = 0;
        string key = "";
        string value = "";
        for (auto i : arr[j + 1])
        {

            if (space == 1 && i != ' ')
            {
                key += i;
                // cout << key<<endl;
            }
            if (space == 3)
            {
                value += i;
            }
            if (i == ' ')
                space++;
        }
        // cout<<key;
        block_variables[key] = value;
    }

    // space=0;
    // key="";
    // value="";
    // for(auto i:firstlast){
    //     if(space==1 && i!=' '){
    //         key+=i;
    //     }
    //     if(space==3){
    //         value+=i;
    //     }
    //     if(i==' ') space++;
    // }
    // // cout << key << endl;

    // block_variables[key]=value;

    for (auto ele : block_variables)
    {
        fout << ele.first << " : ";
        fout << ele.second << endl;
    }

    fin.close();
    fout.close();
    // return 0;
}
