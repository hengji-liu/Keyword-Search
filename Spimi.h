#ifndef SPIMI_H
#define SPIMI_H

#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "Dict.h"
#include "Merger.h"
#include "Util.h"

using namespace std;

class Spimi
{
    public:
        Spimi();
        virtual ~Spimi();
        void start(string docDir, string idxDir);
    protected:
    private:
        ifstream in;
        Dict dict;
        int accumTermsNum;
        int threshold;
        int docID;
        string idxDir;
        regex extractor;
        void processDoc();
        void generateDictIdx(string tmpIdxFile, string idxDir);
};

#endif // SPIMI_H
