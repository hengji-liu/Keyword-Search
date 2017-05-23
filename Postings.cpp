#include "Postings.h"

Postings::Postings()
{
    //ctor
}

Postings::~Postings()
{
    //dtor
}

int Postings::df(){
    return p.size();
}

vector<int> Postings::decode() {
    //TODO
    vector<int> v;
    return v;
}

void Postings::push(int docID, int freq) {
    if (find(docID) == 0) { // new docID
        p.insert(pair<int, int>(docID, freq));
    }else{
        p[docID] += freq;
    }
}

int Postings::find(int docID) {
    map<int, int>::iterator it = p.find(docID);
    if (it != p.end()) return 1;
    else return 0;
}

void Postings::writeToFile(ofstream &out) {
    map<int, int>::iterator it = p.begin();
    for (;it != p.end(); it++) {
        int docID = it->first;
        int freq = it->second;
        out.write((char*)(&docID), 4);
        out.write((char*)(&freq), 4);
    }
}

void Postings::readFromFile(ifstream &in, int len) {
    // buf.clear();
    // for (int i = 0; i < len; i++) {
    //     int x;
    //     in.read((char *)&x, sizeof(int));
    //     buf.push_back(x);
    // }
    // char c;
    // in.read(&c, sizeof(char));
    // bit = c;
    // int a;
    // in.read((char *)&a, sizeof(int));
    // last = a;
    // in.read(&bit, sizeof(char));
    // in.read((char *)&last, sizeof(int));
}
