#include "../include/Spimi.h"

Spimi::Spimi()
{
    threshold = 3;
    docID = 0;
    accumTermsNum = 0;
    }
Spimi::~Spimi()
{
    //dtor
}
int Spimi::getDocNum() {
    return docID;
}
void Spimi::updateDict(vector<string> &v) {
    vector<string>::iterator it = v.begin();
    for (; it != v.end(); it++) {
        dict.insert(*it, docID);
    }
}

// discard intial or trailing non-alphabet char
string Spimi::trim(string& str) {
    int i = 0;
    int j = str.size() - 1;
    while(!isalpha(str[i]) && i <= j) {
        i++;
    }
    while(!isalpha(str[j]) && i <= j) {
        j--;
    }
    // TODO: stemming
    str = str.substr(i, j - i + 1);
    j = str.size();
    for (i = 0; i < j; i++)
        str[i] = tolower(str[i]);
    return str;
}

void Spimi::processDoc() {
    vector<string> v;
    string str;
    while(in>>str) {
        str = trim(str);
        if (str == "")
            continue;
        // cout << str << endl;
        v.push_back(str);
        accumTermsNum++;
        // write tmp idx file when accumTermsNum exceed the threshold
        if (accumTermsNum % threshold == 0) {
            updateDict(v);
            v.clear();
            // char name[100];
            // sprintf(name, "./tmp/b%d", docID / splitNum);
            // dict.writeToFile(name);
            // dict.reset();
        }
    }
    updateDict(v);
}

void Spimi::start(string docDir, string idxDir) {
    // process each doc in the folder
    vector<string> fileNames = util.getFiles(docDir);
    for (int i = 0; i < fileNames.size(); i++) {
        in.open((docDir + "/" + fileNames[i]).c_str(),ios::in);
        processDoc();
        cout << "---" << endl;
        docID++;
        in.close();
    }
    exit(0);
    // if not all idx's are written
    if (accumTermsNum % threshold) { 
        char name[100];
        sprintf(name, "./tmp/b%d", accumTermsNum % threshold + 1);
        dict.writeToFile(name);
    }
    // merge tmp idx
    string name = merger.merge("./tmp");
    cout<<name<<endl;
    generateDictIdx(name, idxDir, idxDir);
    util.delFile(name);
}

void Spimi::generateDictIdx(string tmpIdxFile, string dictFile, string idxFile) {
    in.open(tmpIdxFile.c_str(), ios::binary|ios::in);
    ofstream out2idx(idxFile.c_str(), ios::binary|ios::out);
    map<string, pair<int, int> > mp;
    char term[100], termLen;
    int offset = 0, len, t, df;
    while(!in.eof()) {
        // get term length
        termLen = -1;
        in.read(&termLen, sizeof(char));
        if (termLen == -1) break;
        // get term
        in.read(term, termLen);
        term[termLen] = 0;
        // get df and posting length
        in.read((char *)&df, sizeof(df));
        in.read((char *)&len, sizeof(int));
        // record docFreq and start position of posting list
        mp[term] = make_pair<int, int>(df, offset);
        t = (len * 4) + 1 + 4; // docID as int + bit as char + last docId as int
        offset += t;
        char *buf = new char[t];
        in.read(buf, sizeof(char) * t);
        out2idx.write(buf, sizeof(char) * t);
        delete[] buf;
    }
    cd.generateDict(mp, offset);
    cd.writeToFile(dictFile);
    in.close();
    out2idx.close();
}


