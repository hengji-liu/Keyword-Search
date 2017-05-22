#ifndef SPIMI_H
#define SPIMI_H

#include <cstring>
#include <string>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <regex>
#include "Dict.h"
#include "Util.h"
#include "Merger.h"
#include "CompressedDict.h"
using namespace std;

class Spimi
{
    public:
        Spimi();
        virtual ~Spimi();
        int getDocNum();
        void generateDictIdx(string file, string dictFile, string indexFile);
        void start(string docDir, string idxDir);
    protected:
    private:
        regex extractor;
        ifstream in;
        Dict dict;
        CompressedDict cd;
        Util util;
        Merger merger;
        int accumTermsNum;
        int threshold;
        int docID;
        void processDoc();
        void updateDict(vector<string>& v);
};

#endif // SPIMI_H
