#include "Spimi.h"

Spimi::Spimi(string docDir, string idxDir):
    docDir(docDir), 
    idxDir(idxDir), 
    threshold(1024*1024), 
    docID(0), 
    accumTermsNum(0),
    extractor("[a-zA-Z]{3,}")
    {}

void Spimi::processDoc() {
    vector<string> v;
    string line;
    string term;
    sregex_iterator rend;
    while(getline(in, line)){
        sregex_iterator rit(line.begin(), line.end(), extractor);
        while (rit!=rend) {
            term = rit->str();
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

void Spimi::build() {
    // process each doc in the folder
    vector<string> fileNames = Util::ls(docDir);
    for (int i = 0; i < fileNames.size(); i++) {
        in.open((docDir + "/" + fileNames[i]).c_str(),ios::in);
        processDoc();
        // TODO store <docID, docName>
        docID++;
        in.close();
    }
    // if not all idx's are written
    if (accumTermsNum % threshold) { 
        string idxFile = idxDir + "/tmp" + to_string(accumTermsNum/threshold + 1);
        ofstream out(idxFile, ios::binary|ios::out);
        dict.writeToFile(out);
        out.close();
    }
    // merge tmp 
    string tmpIdxFile = Merger::merge(idxDir);
    generateDictIdx(tmpIdxFile);
    Util::rm(tmpIdxFile);
}

void Spimi::generateDictIdx(string tmpIdxFile) {
    in.open(tmpIdxFile.c_str(), ios::binary|ios::in);
    string t = idxDir+"/t";
    string d = idxDir+"/d";
    string p = idxDir+"/p";
    ofstream o2t(t.c_str(), ios::binary|ios::out);
    ofstream o2d(d.c_str(), ios::binary|ios::out);
    ofstream o2p(p.c_str(), ios::binary|ios::out);

    int t_offset = 0;
    int p_offset = 0;

    char buff[2000*2*sizeof(int)];
    char term[256];
    int termLen = -1;
    in.read((char*)(&termLen), sizeof(int));
    in.read(term, termLen);
    term[termLen] = 0;
    int df;

    while(true){
        in.read((char *)&df, sizeof(int));
        in.read(buff, df*2*sizeof(int));
        o2p.write(buff, df*2*sizeof(int));

        o2t.write(term, termLen);

        o2d.write((char *)&t_offset, sizeof(int));
        o2d.write((char *)&p_offset, sizeof(int));
        t_offset += termLen;
        p_offset += df*2*sizeof(int);
        // next loop
        in.read((char*)(&termLen), sizeof(int));
        if (in.eof())
            break;
        in.read(term, termLen);
        term[termLen] = 0;
    }

    in.close();
    o2t.close();
    o2d.close();
    o2p.close();
}


