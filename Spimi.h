#ifndef SPIMI_H
#define SPIMI_H

#include <cstring>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <regex>
#include "Dict.h"
#include "Util.h"
// #include "Merger.h"
using namespace std;

class Spimi
{
    public:
        Spimi();
        virtual ~Spimi();
        void generateDictIdx(string file, string dictFile, string indexFile);
        void start(string docDir, string idxDir);
    protected:
    private:
        ifstream in;

        Dict dict;
        // Merger merger;

        int accumTermsNum;
        int threshold;
        int docID;
        string idxDir;
        regex extractor;
        void processDoc();
};

#endif // SPIMI_H
