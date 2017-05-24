#ifndef SPIMI_H
#define SPIMI_H

#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "Dict.h"
#include "Merger.h"
#include "Util.h"
#include "porter2_stemmer.h"

using namespace std;

class Spimi
{
    public:
        Spimi(string docDir, string idxDir);
        void build();
    protected:
    private:
        string docDir;
        string idxDir;
        int accumTermsNum;
        int threshold;
        int docID;
        regex extractor;
        Dict dict;
        ifstream in;
        void processDoc();
        void generateDictIdx(string tmpIdxFile);
};

#endif // SPIMI_H
