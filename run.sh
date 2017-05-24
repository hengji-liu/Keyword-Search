rm -r idx
make clean
make
clear
./a3search ./test/simple idx -c num "apple" "iphone"
# ./a3search ./test/simple idx "5" "4" "3" "2" "1"