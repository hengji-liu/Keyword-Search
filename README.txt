Project structure:
- a3search.cpp	---------- 	main workflow
- Spimi.cpp		----------	build idx using single-pass-in-memory-indexing algorithm
- Dict.cpp		----------	data structure, contains a list of <term, postings>
- Postings.cpp	----------	data structure, contains a list of <docID, tf> pair
- Merger.cpp	----------	provides any endpoint to merge all idxes into one
- Searcher.cpp	----------	provides searching functionality
- Util.cpp		----------	list file names (sorted), delete files, etc.
- porter2_stemmer.cpp	--	stemming


Index schema:
- idx in the making	------	for every <term, postings>, write <termLen, term, df, (docID, tf)+>
- final idx		----------	p ~ a list of <docID, tf>
							d ~ a list of <offset in t, termlen, offset in p, df>, sorted according to term lexical order
							t ~ all terms concatenated as one string

When search:
d is sorted and has fixed length entry like <int, int, int, int>,
so first do binary search on d to find the term using <offset in t, termlen>, 
get its postings list using <offset in p, df> and store in map<docID, vector<tf>>

When print:
check vector<tf> has the same size as the number of search terms and write to map<docID, tf_sum>
sort on map value tf_sum to rank the docs,
find file name via docID and print.