#include "Util.h"

// get all file names under a directory
vector<string> Util::ls(string path) {
    DIR *dp;
    struct dirent *dirp;
    vector<string> file_names;
    dp = opendir(path.c_str());
    while((dirp=readdir(dp))!=NULL){
        if((strcmp(dirp->d_name,".")==0)||(strcmp(dirp->d_name,"..")==0))
            continue;
        file_names.push_back(dirp->d_name);
    }
    stable_sort(file_names.begin(), file_names.end());
    return file_names;
}

void Util::rm(string file) {
    file = "rm -f " + file;
    system(file.c_str());
}

void Util::mkdir(string dir){
    string command = "mkdir " + dir;
    system(command.c_str());
}
