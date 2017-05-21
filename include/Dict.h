#ifndef DICT_H
#define DICT_H
#include <map>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "IndexList.h"
using namespace std;
class Dict
{
    public:
        Dict();
        virtual ~Dict();
        // check if term is in the mp
        int find(string term);
        // insert a term
        void insert(string term, int docID);
        void push(int id, int docID);
        // write dict and idx to file
        void writeToFile(char *indexName);
        void reset();
        void output(string s);
    protected:
    private:
        // term count
        int itemNum;
        // <term, termID> mapping
        map<string, int> mp;
        // posting list for every term
        vector<IndexList> list;
        // document frequency
        vector<int> df;
};

#endif // DICT_H
