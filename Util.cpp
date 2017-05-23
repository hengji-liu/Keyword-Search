#include "Util.h"

Util::Util()
{
    //ctor
}

Util::~Util()
{
    //dtor
}

// get all file names under a directory
vector<string> Util::getFiles(string path) {
    DIR *dp;
    struct dirent *dirp;
    vector<string> file_names;
    dp = opendir(path.c_str());
    while((dirp=readdir(dp))!=NULL){
        if((strcmp(dirp->d_name,".")==0)||(strcmp(dirp->d_name,"..")==0))
            continue;
        file_names.push_back(dirp->d_name);
    }
    return file_names;
}

void Util::delFile(string file) {
    file = "rm -f " + file;
    system(file.c_str());
}