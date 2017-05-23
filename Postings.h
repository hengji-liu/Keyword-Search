#ifndef POSTINGS_H
#define POSTINGS_H
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
class Postings
{
    public:
        Postings();
        virtual ~Postings();
        int df();
        void push(int docID, int freq);
        vector<int> decode();
        void writeToFile(ofstream &out);
        void readFromFile(ifstream &in, int len);
    protected:
    private:
        map<int, int> p; // <docID, tf>
        int find(int docID);
};

#endif // POSTINGS_H
