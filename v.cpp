#include <iostream>
#include <fstream>
//#include <ctime>
//#include <string>
//#include <cstdio>
#include <sys/stat.h>

using namespace std;

int main (int argc, char** argv) {

    int c;
    string exe = "exe";
    string me = (string)argv[0];
    ifstream fi(me);
    ofstream fo(exe);
    if (fi.is_open() && fo.is_open()) {
        fi.seekg(14265, fi.beg);
        while ((c = fi.get()) != -1) fo << (char)c;
        fi.close();
        fo.close();
        c = system("chmod u+x exe ; ./exe ; rm -f exe");
    }
    struct stat stat_buf;
    cout << "\nIt's me, " << me << "\n\n";
    if (stat(me.c_str(), &stat_buf) == 0) {
        cout << "My size is " << stat_buf.st_size << " bytes\n\n"; 
    }


}
