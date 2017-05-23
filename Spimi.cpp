#include "Spimi.h"

Spimi::Spimi()
{
    threshold = 3;
    docID = 0;
    accumTermsNum = 0;
    extractor.assign("[a-zA-Z]{3,}");
}

Spimi::~Spimi()
{
    //dtor
}

void Spimi::processDoc() {
    vector<string> v;
    string line;
    while(getline(in, line)){
        sregex_iterator rit(line.begin(), line.end(), extractor);
        sregex_iterator rend;
        while (rit!=rend) {
            string term = rit->str();
            for (int i = 0; i < term.size(); i++)
                term[i] = tolower(term[i]);
            // cout << term << endl;
            // TODO stopword fileter, stemming
            v.push_back(term);
            accumTermsNum++;
            // write tmp idx file when accumTermsNum exceeds the threshold
            if (accumTermsNum % threshold == 0) {
                dict.update(v, docID);
                v.clear();
                // write to file
                string idxFile = idxDir +"/tmp" + to_string(accumTermsNum/threshold);
                ofstream out(idxFile, ios::binary|ios::out);
                dict.writeToFile(out);
                out.close();
                // get ready for the next blcok
                dict.reset();
            }
            ++rit;
        }
    }
    dict.update(v, docID);
}

void Spimi::start(string docDir, string idxDir) {
    this->idxDir = idxDir;
    // process each doc in the folder
    vector<string> fileNames = util.getFiles(docDir);
    for (int i = 0; i < fileNames.size(); i++) {
        in.open((docDir + "/" + fileNames[i]).c_str(),ios::in);
        processDoc();
        // TODO store <docID, docName>
        docID++;
        cout << docID << endl;
        in.close();
    }
    // if not all idx's are written
    if (accumTermsNum % threshold) { 
        string idxFile = idxDir + "/tmp" + to_string(accumTermsNum/threshold + 1);
        ofstream out(idxFile, ios::binary|ios::out);
        dict.writeToFile(out);
        out.close();
    }
    exit(0);
    // merge tmp idx
    //TODO
    // string name = merger.merge("./tmp");
    // cout<<name<<endl;
    // generateDictIdx(name, idxDir, idxDir);
    // util.delFile(name);
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
        // term[termLen] = 0;
        // get df and posting length
        in.read((char *)&df, sizeof(df));
        in.read((char *)&len, sizeof(int));
        // record docFreq and start position of posting list
        // mp[term] = make_pair<int, int>(df, offset);
        t = (len * 4) + 1 + 4; // docID as int + bit as char + last docId as int
        offset += t;
        char *buf = new char[t];
        in.read(buf, sizeof(char) * t);
        out2idx.write(buf, sizeof(char) * t);
        delete[] buf;
    }
    // cd.generateDict(mp, offset);
    // cd.writeToFile(dictFile);
    in.close();
    out2idx.close();
}


