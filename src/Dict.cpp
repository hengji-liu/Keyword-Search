#include "../include/Dict.h"

Dict::Dict()
{
    itemNum = 0;
    list.clear();
    mp.clear();
    df.clear();
}

Dict::~Dict()
{
    //dtor
}

void Dict::output(string s) {
    int id = find(s);
    vector<int> v = list[id].decode();
    int l = v.size();
    //cout<<l<<endl;
    for (int i = 0; i < l; i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
void Dict::push(int id, int docID) {
    //cout<<id<<" "<<docID<<endl;
    if (id == (int)list.size()) { // new indexList for a new term
        IndexList il;
        list.push_back(il);
        df.push_back(0);
    }
    list[id].push(docID);
    df[id] = df[id] + 1;
}
int Dict::find(string term) {
    map<string, int>::iterator it = mp.find(term);
    if (it != mp.end()) return it->second;
    else return -1;
}
void Dict::insert(string term, int docID) {
    int id;
    if ((id = find(term)) != -1) { // termId is in the dict
        push(id, docID);
    } else {
        mp[term] = itemNum++;
        push(itemNum - 1, docID);
    }
}
void Dict::writeToFile(char *indexName) {

    ofstream out(indexName, ios::binary|ios::out);
    map<string, int>::iterator it = mp.begin();

    for (;it != mp.end(); it++) {
        const char* str = it->first.c_str();
        char l = strlen(str);
        // write term length and term
        out.write(&l, sizeof(char));
        out.write(str, l);
        // write doc freq of the term
        out.write((char *)&df[it->second], sizeof(int));
        // write
        list[it->second].writeOffset(out); // postingList.writeOffset(out)
        list[it->second].writeToFile(out);
    }

    out.close();
}
