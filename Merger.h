#ifndef MERGER_H
#define MERGER_H

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Util.h"
#include "Postings.h"

using namespace std;

class Merger
{
    public:
        // merge all files in that dir
        static string merge(string idxDir);
    protected:
    private:
        static void mergeTwo(const char *file1, const char* file2, const char *outfile);
        static void readTerm(ifstream &in, char *s); // read termLen and term
};

#endif // MERGER_H
