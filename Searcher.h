#ifndef SEARCHER_H
#define SEARCHER_H

#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include "Util.h"

using namespace std;

class Searcher
{
    public:
        Searcher(string docDir, string idxDir);
        int search(const char* term);
        void show();
    protected:
    private:
        string docDir;
        string idxDir;
        int searchCount;
        map<int, vector<int>> mp; // <docID, {tf}>
        map<int, double> scores; // <docID, score>
        int binarySearch(ifstream &d, ifstream &t, const char* term);
        struct CmpByVal{
            bool operator()(const pair<int, double> &l,const pair<int, double> &r){
                return l.second < r.second;
            }
        };
    };

#endif // SEARCHER_H
