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
        map<int, int> scores; // <docID, score>
        int binarySearch(ifstream &d, ifstream &t, const char* term);
        struct CmpByVal{
            // score descending, if tie, docID ascending
            bool operator()(const pair<int, int> &l,const pair<int, int> &r){
                return (l.second > r.second) || (!(l.second > r.second) && (l.first < r.first)) ;
            }
        };
    };

#endif // SEARCHER_H
