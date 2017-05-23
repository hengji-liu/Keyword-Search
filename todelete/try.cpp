#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
string s1 = "abcd";
string s2 = "AB";
fstream out("dump", ios::out);
out << s1;
out << s2;
out.close();

char* s3 = new char[4];
char* s4 = new char[2];
fstream in("dump", ios::in);
in.read(s3, 4);
in.read(s4, 2);
cout << string(s3) <<endl;
cout << string(s2) <<endl;
cout << s2 <<endl;

in.close();
}