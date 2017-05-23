#ifndef UTIL_H
#define UTIL_H

#include <cstring>
#include <string>
#include <vector>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
class Util
{
    public:
        Util();
        virtual ~Util();
        static vector<string> ls(string path);
        static void rm(string file);
        static void mkdir(string dir);
    protected:
    private:
};

#endif // UTIL_H
