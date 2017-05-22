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
        void push(int docID, int freq);
        vector<int> decode();
        void writeToFile(ofstream &out);
        void readFromFile(ifstream &in, int len);
    protected:
    private:
        map<int, int> pl; // <docID, freq>
        int find(int docID);
};

#endif // POSTINGS_H
