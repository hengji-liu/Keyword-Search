#include "Merger.h"

Merger::Merger()
{
    //ctor
}

Merger::~Merger()
{
    //dtor
}

void Merger::readTerm(ifstream &in, char *term) {
    int termLen =  -1;
    in.read((char*)(&termLen), sizeof(int));
    if (termLen == -1) { // eof
        term[0] = 0; 
        return;
    }
    in.read(term, termLen);
    term[termLen] = 0; // \0 indicates the end of string
}

void Merger::writeMergedPostings(ifstream &in1, ifstream &in2, int df1, int df2, ofstream &out){
    int docID1;
    int docID2;
    int tf1;
    int tf2;
    in1.read((char *)&docID1, sizeof(int));
    in1.read((char *)&tf1, sizeof(int));
    in2.read((char *)&docID2, sizeof(int));
    in2.read((char *)&tf2, sizeof(int));
    while(df1 > 0 && df2 > 0) {
        if (docID1 < docID2){
            df1--;
            out.write((char*)(&docID1), sizeof(int));
            out.write((char*)(&tf1), sizeof(int));
            if (df1 > 0){
                in1.read((char *)&docID1, sizeof(int));
                in1.read((char *)&tf1, sizeof(int));
            }
         } else if (docID1 > docID2){
            df2--;
            out.write((char*)(&docID2), sizeof(int));
            out.write((char*)(&tf2), sizeof(int));
            if (df2 >0){
                in2.read((char *)&docID2, sizeof(int));
                in2.read((char *)&tf2, sizeof(int));
            }
        } else {
            df1--;
            df2--;
            int tf_new = tf1+tf2;
            out.write((char*)(&docID1), sizeof(int));
            out.write((char*)(&tf_new), sizeof(int));
            if (df1 > 0 && df2 > 0){
                in1.read((char *)&docID1, sizeof(int));
                in1.read((char *)&tf1, sizeof(int));
                in2.read((char *)&docID2, sizeof(int));
                in2.read((char *)&tf2, sizeof(int));
            }
        }
    }
    if (df1 > 0){
        out.write((char*)(&docID1), sizeof(int));
        out.write((char*)(&tf1), sizeof(int));
        // write the rest of in1
        if (df1 > 1){
            int bufsiz= df1*2*sizeof(int);
            char buff[bufsiz]; // rest {doc id, tf} of this term
            in1.read(buff, bufsiz);
            out.write(buff, bufsiz);
        }
    }
    if (df2 > 0){
        out.write((char*)(&docID2), sizeof(int));
        out.write((char*)(&tf2), sizeof(int));
        // write the rest of a2
        if (df2 > 1){
            int bufsiz= df2*2*sizeof(int);
            char buff[bufsiz]; // rest {doc id, tf} of this term
            in2.read(buff, bufsiz);
            out.write(buff, bufsiz);
        }
    }
}

void Merger::mergeTwo(const char *file1, const char *file2, const char *outfile) {
    ifstream in1(file1, ios::binary|ios::in);
    ifstream in2(file2, ios::binary|ios::in);
    ofstream out(outfile, ios::binary|ios::out);
    char term1[256];
    char term2[256];
    readTerm(in1, term1);
    readTerm(in2, term2);
    int df, df2;
    char buff[2000*2*sizeof(int)]; // max 2000 {doc id, tf}
    while(term1[0] != 0 && term2[0] != 0) {
        if (strcmp(term1, term2) < 0) {
            in1.read((char *)&df, sizeof(int));
            in1.read(buff, df*2*sizeof(int));
            // write termLen, term, df and all {docID, tf}
            int termLen = strlen(term1);
            out.write((char*)(&termLen), sizeof(int));
            out.write(term1, termLen);
            out.write((char*)(&df), sizeof(int));
            out.write(buff, df*2*sizeof(int));
            // next loop
            readTerm(in1, term1);
        } else if (strcmp(term1, term2) > 0) {
            in2.read((char *)&df, sizeof(int));
            in2.read(buff, df*2*sizeof(int));
            // write termLen, term, df and all {docID, tf}
            int termLen = strlen(term2);
            out.write((char*)(&termLen), sizeof(int));
            out.write(term2, termLen);
            out.write((char*)(&df), sizeof(int));
            out.write(buff, df*2*sizeof(int));
            // next loop
            readTerm(in2, term2);
        } else {
            in1.read((char *)&df, sizeof(int));
            in2.read((char *)&df2, sizeof(int));
            int df_new = df+df2;
            // write termLen, term, df
            int termLen = strlen(term1);
            out.write((char*)(&termLen), sizeof(int));
            out.write(term1, termLen);
            out.write((char*)(&df_new), sizeof(int));
            // write merged {docID, tf}
            writeMergedPostings(in1, in2, df, df2, out);
            // next loop
            readTerm(in1, term1);
            readTerm(in2, term2);
        }
    }
    if (term1[0] != 0){
        int termLen = strlen(term1);
        out.write((char*)(&termLen), sizeof(int));
        out.write(term1, termLen);
        out << in1.rdbuf();
    }
    if (term2[0] != 0){
        int termLen = strlen(term2);
        out.write((char*)(&termLen), sizeof(int));
        out.write(term2, termLen);
        out << in2.rdbuf();
    }
    in1.close();
    in2.close();
    out.close();
}

string Merger::merge(string idxDir) {
    vector<string> fileNames;
    int idx = 0;
    while(true) {
        if(fileNames.size() <= 1) {
            fileNames = Util::ls(idxDir);
            for (int i = 0; i < (int)fileNames.size(); i++) {
                fileNames[i] = idxDir + "/" + fileNames[i];
            }
            // only one idx file left
            if (fileNames.size() <= 1) break;
        }
        string idxFile = idxDir + "/merge" + to_string(idx++);
        // cout << "merging " << fileNames[0] << " and "<<fileNames[1] << " to " << idxFile << endl;
        mergeTwo(fileNames[0].c_str(),fileNames[1].c_str(), idxFile.c_str());
        Util::rm(fileNames[0]);
        Util::rm(fileNames[1]);
        fileNames.erase(fileNames.begin());
        fileNames.erase(fileNames.begin());
    }
    return fileNames[0];
}
