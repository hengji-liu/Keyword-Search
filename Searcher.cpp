#include "Searcher.h"

Searcher::Searcher(string idxDir): idxDir(idxDir), searchCount(0){}

int Searcher::search(const char* term) {
    ifstream p(idxDir+"/p", ios::binary|ios::in);
    ifstream d(idxDir+"/d", ios::binary|ios::in);
    ifstream t(idxDir+"/t", ios::binary|ios::in);

    int result = binarySearch(d,t,term);

    if (-1 != result){ // term is found
    	// get term postings
  		int d_offset = result * 4 * sizeof(int) + 2 * sizeof(int);
  		int p_offset;
  		int df;
  		d.seekg(d_offset);
	    d.read((char*)(&p_offset), sizeof(int));
	    d.read((char*)(&df), sizeof(int));
	    p.seekg(p_offset);
	    for (int i = 0; i < df; ++i){
	    	// read docID and tf
	    	int docID;
	    	int tf;
	    	p.read((char*)(&docID), sizeof(int));
	    	p.read((char*)(&tf), sizeof(int));
	    	// push to map, same logic as postings
    		map<int, int>::iterator it = mp.find(docID);
    		if (it == mp.end()){ // new docID
        		mp.insert(pair<int, int>(docID, tf));
    		}else{
        		mp[docID] += tf;
    		}
	    }
    }

    p.close();
    d.close();
    t.close();

    searchCount++;

    if (-1 != result){
    	return 1; // found
    }else{
    	return 0;
    }
}

int Searcher:: binarySearch(ifstream &d, ifstream &t, const char* term){
    streampos begin = d.tellg();
    d.seekg(0, d.end);
    streampos end = d.tellg();
    int d_size = end - begin; // in bytes
    // binary search to find the term
    int t_offset;
	char candidate[256];
    int candidateLen;
    int low = 0;
    int high = d_size/(4*sizeof(int))-1;
    while(low <= high){ // binary search on d space
        int mid = (low + high)/2;

        d.seekg(mid * 4 * sizeof(int));
	    d.read((char *)(&t_offset), sizeof(int));
	    d.read((char *)(&candidateLen), sizeof(int));
	    t.seekg(t_offset);
	    t.read(candidate, candidateLen);
	    candidate[candidateLen] = 0;
	    // cout << candidate << " " << term << " " << strcmp(candidate, term)<< endl;
	    if (strcmp(candidate, term) > 0)
	    	high = mid - 1;
        else if (strcmp(candidate, term) < 0)
            low = mid + 1;
        else // term is found
            return mid;
    }
    return -1;
}

void Searcher::show() {
	// rank
    map<int, int>::iterator it = mp.begin();
    for (;it != mp.end(); it++) {
        int docID = it->first;
        int tfsum = it->second;
        scores.insert(pair<int, double>(docID,(double)tfsum/searchCount));
    }
    // print
    map<int, double>::iterator ite = scores.begin();
    for (;ite != scores.end(); ite++) {
        double score = ite->second;
        int docID = ite->first;
    }
    //TODO sort according to value and print file name
   
}

