#include "../include/Dict.h"

Dict::Dict()
{
    termsNum = 0;
    list.clear();
    mp.clear();
    df.clear();
}

Dict::~Dict()
{
    //dtor
}

void Dict::push(int termID, int docID) {
    // new indexList if a new term
    if (termID == (int)list.size()) {
        IndexList il;
        list.push_back(il);
        df.push_back(0);
    }
    // TODO: indexList should also store term frequency
    list[termID].push(docID); 
    df[termID] = df[termID] + 1;
}

void Dict::insert(string term, int docID) {
    int termID;
    if ((termID = find(term)) != -1) { // termID is in the dict
        push(termID, docID);
    } else {
        push(termsNum, docID);
        mp[term] = termsNum++; // <term, termID>
    }
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

int Dict::find(string term) {
    map<string, int>::iterator it = mp.find(term);
    if (it != mp.end()) return it->second;
    else return -1;
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
