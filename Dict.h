#ifndef DICT_H
#define DICT_H

#include <map>
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
        void reset();
        // check if term is in the mp
        int find(string term);
        // update dict with a vector of terms
        void update(vector<string> &v, int docID);
        // write dict and idx to file
        void writeToFile(ofstream &out);
        void output(string s);
    protected:
    private:  
        // <term, postings>, sorted automatically
        map<string, Postings> d;
};

#endif // DICT_H
