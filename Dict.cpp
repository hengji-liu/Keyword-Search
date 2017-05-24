#include "Dict.h"

void Dict::reset() {
    d.clear();
}

void Dict::update(vector<string> &v, int docID) {
    vector<string>::iterator it = v.begin();
    string term;
    for (; it != v.end(); it++) {
        term = *it;
        // if a new term, create a posting
        if (find(term) == 0) {
            Postings p;
            d.insert(pair<string, Postings>(term, p));
        }
        // update tf
        d[term].push(docID, 1);
    }
}

int Dict::find(string term) {
    map<string, Postings>::iterator it = d.find(term);
    if (it != d.end()) return 1;
    else return 0;
}

void Dict::writeToFile(ofstream &out) {
    map<string, Postings>::iterator it = d.begin();
    string term;
    Postings posting;
    int termLen;
    for (;it != d.end(); it++) {
        term = it->first;
        posting = it->second;
        termLen = term.size();
        // write term length, term 
        out.write((char*)(&termLen), sizeof(int));
        out.write(term.c_str(), termLen);
        // write df and postings: <docID, tf>
        posting.writeToFile(out);
    }
}
