#include "Postings.h"

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
    int df = p.size();
    out.write((char*)(&df), sizeof(int));
    map<int, int>::iterator it = p.begin();
    for (;it != p.end(); it++) {
        int docID = it->first;
        int freq = it->second;
        // cout << docID << " " << freq << endl;
        out.write((char*)(&docID), sizeof(int));
        out.write((char*)(&freq), sizeof(int));
    }
}
