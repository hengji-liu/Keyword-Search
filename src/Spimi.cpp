#include "../include/Spimi.h"

Spimi::Spimi()
{
    //ctor
}

Spimi::~Spimi()
{
    //dtor
}
int Spimi::getItemNum() {
    return itemNum;
}
int Spimi::getDocNum() {
    return docID;
}
int Spimi::getTokenNum() {
    return tokenNum;
}
double Spimi::getAveLen() {
    return tokenNum * 1.0 / docID;
}
void Spimi::updateDict(set<string> &s) {
    //cout<<"updateDict"<<endl;
    set<string>::iterator it = s.begin();
    for (; it != s.end(); it++) {
        dict.insert(*it, docID);
    }
}
string Spimi::trim(string& str) {
    int st;
    if ((st = str.find("<title>")) != -1)  {
        str = str.substr(st + 7);
    }
    if ((st = str.find("<speaker>")) != -1)  {
        str = str.substr(st + 9);
    }
    if ((st = str.find("</title>")) != -1)  {
        str = str.substr(0, st);
    }
    if ((st = str.find("</speaker>")) != -1)  {
        str = str.substr(0, st);
    }
    int i = 0, j = str.size() - 1, t;
    while(!isalpha(str[i]) && i <= j) {
        i++;
    }
    while(!isalpha(str[j]) && i <= j) {
        j--;
    }
    t = j;
    while(str[t] != '\'' && t >= 0) {
        t--;
    }
    if (t >= 0) j = t - 1;
    str = str.substr(i, j - i + 1);
    j = str.size();
    for (i = 0; i < j; i++)
        str[i] = tolower(str[i]);
    return str;
}
void Spimi::processDoc() {
    set<string> s;
    string str;
    while(in>>str) {
        if (str.find("</DOC>") != -1) {
            updateDict(s);
            return;
        }
        if (str.find("<!--") != -1) {
            while(in>>str) {
                if (str.find("</DOC>") != -1) {
                    break;
                }
            }
            updateDict(s);
            return;
        }
        str = trim(str);
        if (str == "") continue;
        tokenNum++;
        s.insert(str);
    }
}
void Spimi::processFile() {
    string str;
    while(in>>str) {
        if (str.find("<DOC>") != -1) {
            docID++;
            in>>str;
            cout<<str<<endl;
            processDoc();
        } else {
            cout<<"发生错误:"<<docID<<endl;
        }
        //printf("%d\n", docID);
        if (docID % splitNum == 0) { // write tmp idx file every splitNum
            char name[100];
            sprintf(name, "./tmp/b%d", docID / splitNum);
            dict.writeToFile(name);
            dict.reset();
        }
    }
}
void Spimi::start(string path, int splitNum, string dictFile, string indexFile) {
    dict.reset();
    this->splitNum = splitNum;
    vector<string> fileNames = util.getFiles(path);
    int size = fileNames.size();
    docID = 0;
    tokenNum = 0;
    for (int i = size - 1; i >= 0; i--) {
        in.open((path + "/" + fileNames[i]).c_str(),ios::in);
        // cout<<"处理文件: "<<path + "/" + fileNames[i]<<endl;
        processFile();
        cout<<"文件处理完成"<<endl;
        in.close();
    }
    if (docID % splitNum) { // if not all idx's are written
        char name[100];
        sprintf(name, "./tmp/b%d", docID / splitNum + 1);
        dict.writeToFile(name);
    }
    // merge tmp idx
    string name = merger.merge("./tmp");
    cout<<name<<endl;
    generateDictIdx(name, dictFile, indexFile);
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


