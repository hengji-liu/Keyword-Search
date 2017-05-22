#include "../include/Dict.h"

Dict::Dict()
{
    //ctor
}

Dict::~Dict()
{
    //dtor
}

void Dict::update(string term, int docID) {
    // if a new term, create a pl
    if (find(term) == 0) { 
        Postings p;
        mp.insert(pair<string, Postings>(term, p));
    }
    // update tf
    mp[term].push(docID, 1);
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
    map<string, Postings>::iterator it = mp.find(term);
    if (it != mp.end()) return 1;
    else return 0;
}

void Dict::writeToFile(char *indexName) {

    // ofstream out(indexName, ios::binary|ios::out);
    // map<string, int>::iterator it = mp.begin();

    // for (;it != mp.end(); it++) {
    //     const char* str = it->first.c_str();
    //     char l = strlen(str);
    //     // write term length and term
    //     out.write(&l, sizeof(char));
    //     out.write(str, l);
    //     // write doc freq of the term
    //     out.write((char *)&df[it->second], sizeof(int));
    //     // write
    //     list[it->second].writeOffset(out); // Postings.writeOffset(out)
    //     list[it->second].writeToFile(out);
    // }

    // out.close();
}
