#ifndef SEARCHER_H
#define SEARCHER_H

#include <cstring>
#include <map>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

class Searcher
{
    public:
        Searcher(string idxDir);
        int search(const char* term);
        void show();
    protected:
    private:
        string idxDir;
        int searchCount;
        map<int, int> mp; // <docID, tf_sigma>
        map<int, double> scores; // <docID, score>
        int binarySearch(ifstream &d, ifstream &t, const char* term);
    };

#endif // SEARCHER_H
