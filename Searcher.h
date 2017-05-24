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
        map<int, vector<int>> mp; // <docID, {tf}>
        map<int, double> scores; // <docID, score>
        int binarySearch(ifstream &d, ifstream &t, const char* term);
        void rank();
    };

#endif // SEARCHER_H
