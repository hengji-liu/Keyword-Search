a3search: *.cpp *.h
	g++ -std=c++11 -O3 *.h *.cpp -o a3search

clean:
	rm a3search
