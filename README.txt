//TODO

dict: dict of a block, it receives <term, docid>
	map<term, PostingsList>

postingsList:
	map<docID, term freq>

for every <term, PostingsList> in mp write {termLen, term, df, {docid, termfreq}}



postings list: for each term {docID, termfreq}, 4Byte+4Byte
dictionary:	for each term {offset in string, termlen, offset in posting list, df} 4Byte+4Byte+4Byte+4byte // could use 4+1+4+2 but idx size is not the primary constraint in this assignment
terms:		all terms as a string

dict sorted in lexicon order, do binary search (compare lexicon order) to find dict entry
may need to read 2 dictNodes to decide read size	