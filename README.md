# Keyword-Search
SPIMI, inverted index, Data Compression Course Assignment

Thanks to longmenwaideyu. Very neat and well-structed code, easy to understand.<br/>
His solution can roughly fit into this assignment. This would save me a lot of time.<br/>
But this project still need to be modified, some of the major changes would be:<br/>
1. different doc identificaton and tokenization
2. some stemming to be added
3. may change gamma code to variant byte to ease the computation consumption, dict and idx format may change accordingly
4. keyword search to be added and ranking to be added

<br/>
<br/>
Project structure: <br/>
- a3search.cpp	---------- 	main workflow <br/>
- Spimi.cpp		----------	build idx using single-pass-in-memory-indexing algorithm <br/>
- Dict.cpp		----------	data structure, contains a list of <term, postings> <br/>
- Postings.cpp	----------	data structure, contains a list of <docID, tf> pair <br/>
- Merger.cpp	----------	provides any endpoint to merge all idxes into one <br/>
- Searcher.cpp	----------	provides searching functionality <br/>
- Util.cpp		----------	list file names (sorted), delete files, etc. <br/>
- porter2_stemmer.cpp	--	stemming <br/>
<br/>
Index schema: <br/>
- idx in the making	------	for every <term, postings>, write <termLen, term, df, (docID, tf)+> <br/>
- final idx		----------	p ~ a list of <docID, tf> <br/>
							d ~ a list of <offset in t, termlen, offset in p, df>, sorted according to term lexical order <br/>
							t ~ all terms concatenated as one string <br/>
<br/>
When search: <br/>
d is sorted and has fixed length entry like <int, int, int, int>, <br/>
so first do binary search on d to find the term using <offset in t, termlen>, <br/>
get its postings list using <offset in p, df> and store in map<docID, vector<tf>> <br/>
<br/>
When print: <br/>
check vector<tf> has the same size as the number of search terms and write to map<docID, tf_sum> <br/>
sort on map value tf_sum to rank the docs, <br/>
find file name via docID and print. <br/>