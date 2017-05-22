#ifndef DICT_H
#define DICT_H
#include <map>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "Postings.h"
using namespace std;
class Dict
{
    public:
        Dict();
        virtual ~Dict();
        // check if term is in the mp
        int find(string term);
        // update dict with a term occurrence
        void update(string term, int docID);
        // write dict and idx to file
        void writeToFile(char *indexName);
        void output(string s);
    protected:
    private:  
        // <term, postings>
        map<string, Postings> mp;
};

#endif // DICT_H
