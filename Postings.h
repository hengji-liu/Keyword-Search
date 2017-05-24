#ifndef POSTINGS_H
#define POSTINGS_H

#include <vector>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

class Postings
{
    public:
        void push(int docID, int freq);
        void writeToFile(ofstream &out);
    protected:
    private:
        map<int, int> p; // <docID, tf>
        int find(int docID);
};

#endif // POSTINGS_H
