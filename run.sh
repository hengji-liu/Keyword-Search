rm -r idx
make clean
make
clear
./main ./test/simple idx -c num "1" "2" "3" "4" "5"
# ./a3search dest idx "5" "4" "3" "2" "1"