#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include "Spimi.h"
#include "Indexer.h"

using namespace std;

int main(int argc, char* argv[])
{
    string docDir = argv[1];
    string idxDir = argv[2];

    // get search terms
    string arg3 = argv[3];
    vector<string> terms;
    if ("-c" == arg3) 
    {
        string num = argv[4];
        vector<string> tmp(argv+5, argv+argc);
        terms = tmp;
    }else{
        vector<string> tmp(argv+3, argv+argc);
        terms = tmp;
    }
    // if no idx, construct idx
    struct stat buff;
    bool idxExists = (stat(idxDir.c_str(), &buff) == 0);
    if (!idxExists)
    {
        string command = "mkdir " + idxDir;
        system(command.c_str());
        Spimi spimi;
        spimi.start(docDir, idxDir);
    }

    // cout<<"文档数量:"<<spimi.getDocNum()<<endl;

    // Indexer indexer;
    // indexer.readFromFile("dict", "index");
    // cout<<"词项数目:"<<indexer.getItemNum()<<endl;
    // int df;
    // cout<<"小写字母单词: 输出倒排索引\n例如输入balabala"<<endl;
    // while(true) {
    //     string s;
    //     cin>>s;
    //     vector<int> v = indexer.find(s, df);
    //     cout<<"df:"<<df<<" docID:";
    //     for (int i = 0; i < v.size(); i++) {
    //         cout<<" "<<v[i];
    //     }
    //     cout<<endl;
    // }
    return 0;
}
