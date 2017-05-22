#include "../include/Postings.h"

Postings::Postings()
{
    //ctor
}

Postings::~Postings()
{
    //dtor
}

vector<int> Postings::decode() {
    //TODO
    vector<int> v;
    return v;
}

void Postings::push(int docID, int freq) {
    if (find(docID) == 0) { // new docID
        pl.insert(pair<int, int>(docID, freq));
    }else{
        pl[docID] += freq;
    }
}

int Postings::find(int docID) {
    map<int, int>::iterator it = pl.find(docID);
    if (it != pl.end()) return 1;
    else return 0;
}

void Postings::writeToFile(ofstream &out) {
    // int len = buf.size();
    // for (int i = 0; i < len; i++) {
    //     int x = buf[i];
    //     out.write((char *)(&x), sizeof(int));
    // }
    // char c = bit;
    // // cout << unsigned(c) << endl;
    // out.write(&c, sizeof(char));
    // out.write((char *)&last, sizeof(int));
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
