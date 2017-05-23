#ifndef MERGER_H
#define MERGER_H
#include <cstring>
#include <string>
#include <fstream>
#include "Util.h"
#include "Postings.h"
#include <vector>
using namespace std;
class Merger
{
    public:
        Merger();
        virtual ~Merger();
        // merge all files in that dir
        static string merge(string idxDir);
    protected:
    private:
        static void mergeTwo(const char *file1, const char* file2, const char *outfile);
        static void readTerm(ifstream &in, char *s); // read termLen and term
        static void writeMergedPostings(ifstream &in1, ifstream &in2, int df1, int df2, ofstream &out);
};

#endif // MERGER_H
