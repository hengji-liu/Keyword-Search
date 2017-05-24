#include "Dict.h"

Dict::Dict()
{
    //ctor
}

Dict::~Dict()
{
    //dtor
}

void Dict::reset() {
    d.clear();
}

void Dict::update(vector<string> &v, int docID) {
    vector<string>::iterator it = v.begin();
    for (; it != v.end(); it++) {
        string term = *it;
        // if a new term, create a posting
        if (find(term) == 0) {
            Postings p;
            d.insert(pair<string, Postings>(term, p));
        }
        // update tf
        d[term].push(docID, 1);
    }
}

void Dict::output(string s) {
    // int id = find(s);
    // vector<int> v = list[id].decode();
    // int l = v.size();
    // //cout<<l<<endl;
    // for (int i = 0; i < l; i++) {
    //     cout<<v[i]<<" ";
    // }
    // cout<<endl;
}

int Dict::find(string term) {
    map<string, Postings>::iterator it = d.find(term);
    if (it != d.end()) return 1;
    else return 0;
}

void Dict::writeToFile(ofstream &out) {
    map<string, Postings>::iterator it = d.begin();
    for (;it != d.end(); it++) {
        string term = it->first;
        Postings posting = it->second;
        int termLen = term.size();
        // write term length, term 
        out.write((char*)(&termLen), sizeof(int));
        out.write(term.c_str(), termLen);
        // write df and postings: <docID, tf>
        posting.writeToFile(out);
    }
}
