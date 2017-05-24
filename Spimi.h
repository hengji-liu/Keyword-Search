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
        void generateDictIdx(string file, string dictFile, string indexFile);
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
};

#endif // SPIMI_H
