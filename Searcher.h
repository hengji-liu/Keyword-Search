#ifndef SEARCHER_H
#define SEARCHER_H

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
        void search(string term);
        void show();
    protected:
    private:
        string idxDir;
        map<int, vector<int>> mp; // <docID, {tf}>
        map<int, double> scores; // <docID, score>
        void rank();
    };

#endif // SEARCHER_H
