#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
    int i;
    // get all the args
    string destFolder = argv[1];
    string idxFolder = argv[2];
    string arg3 = argv[3];
    vector<string> terms;
    if ("-c" == arg3) {
        string num = argv[4];
        vector<string> tmp(argv+5, argv+argc);
        terms = tmp;
    }else{
        vector<string> tmp(argv+3, argv+argc);
        terms = tmp;
    }
    // for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it) {
    //     cout << *it << endl;
    // }
    string str;
    fstream in("test/legal1/06_47.xml", ios::in);
    while(in>>str) {
        cout << str << endl;
    }

    // create idx
    // if (bwt_size > IDX_SIZE) { // use external idx
    //     // check idx exsitence
    //     struct stat buff;
    //     bool idx_exists = (stat(argv[2], &buff) == 0);
    //     // init

    //     // see if idx exists, if not then create. restore anyway for search.
    //     buffer = new char[bwt_size - (IDX_RUN - 1) * fetch_size];
    //     if (!idx_exists) {
    //         idx.open(argv[2], fstream::out);
    //         makeExtIdx();
    //         idx.close();
    //     }
    //     idx.open(argv[2], fstream::in);
    //     for (i = 0; i < IDX_ARR_SIZE; ++i)
    //         idx.read((char*)(&idx_arr[i]), 4);
    //     idx.close();
    // }
    // else { // use in-memory idx, same size as the external one

    // }

    // // get search terms
    // vector<string> terms(argv + 3, argv + argc);

    // // check [
    // string tmp = terms[0];
    // for (i = 1; i < terms.size(); ++i)
    //     tmp += terms[i];
    // size_t found = tmp.find('[');
    // if (found != string::npos) // find [
    //     return 0;

    // delete [] buffer;
    // bwt.close();
}