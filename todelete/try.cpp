#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
int i = 0;
fstream out("dump", ios::out);
out.write((char*)(&i), sizeof(int));
out.close();

int j;
fstream in("dump", ios::in);
in.read((char *)&j, sizeof(int));
cout << j <<endl;
in.close();
}