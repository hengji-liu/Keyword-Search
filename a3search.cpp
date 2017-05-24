#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include "Spimi.h"
#include "Searcher.h"

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
        Util::mkdir(idxDir);
        Spimi spimi(docDir, idxDir);
        spimi.build();
    }
    // search, rank and output results
    Searcher searcher(docDir, idxDir);
    for (vector<string>::const_iterator iter = terms.cbegin(); iter != terms.cend(); iter++){
        string term = *iter;
        int found = searcher.search(term.c_str());
        if (0 == found){ // term not found
            cout << endl;
            return 0;
        }
    }
    searcher.show();

    return 0;
}
