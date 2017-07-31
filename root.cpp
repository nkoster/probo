#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
    uid_t uid=getuid();
    if (uid == 0) cout << "I am root!\n";
    cout << "UID=" << uid << "\n";
}