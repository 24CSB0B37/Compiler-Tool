#include "../include/debugger.h"
#include <cstdio>
#include <fstream>
using namespace std;

string cleangdb(const string &s)
{
    string out;
    for (char c : s)
    {
        if (c == '\t')  out += ' ';        // tab to space
        else if (c == '\n') out += ' ';    // newline to space
        else if (c == '\r') continue;      // strip CR
        else if (c == '\"') out += "'";    // double quote to single
        else if (c == '\\') out += "/";    // backslash to slash
        else out += c;
    }
    return out;
}

string gettrace()
{
    FILE *check = fopen("./program", "r");
    if (!check) return "GDB_ERROR: ./program not found";
    fclose(check);

    int gdb_check = system("which gdb > /dev/null 2>&1");
    if (gdb_check != 0) return "GDB_ERROR: gdb not installed";

    FILE *f = fopen("/tmp/gdb_cmds.txt", "w");
    if (!f) return "GDB_ERROR: could not write gdb commands";

    fprintf(f, "set pagination off\n");
    fprintf(f, "set debuginfod enabled off\n");  // stop debuginfod prompt
    fprintf(f, "set stack-cache off\n");          // disable stack cache
    fprintf(f, "run\n");
    fprintf(f, "bt full\n");
    fprintf(f, "info locals\n");
    fprintf(f, "frame 0\n");
    fprintf(f, "list\n");
    fprintf(f, "quit\n");
    fclose(f);

    string cmd = "ulimit -s 8192; timeout 15 gdb -batch -x /tmp/gdb_cmds.txt ./program 2>&1";

    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "GDB_ERROR: popen failed";

    char buffer[512];
    string out;
    while (fgets(buffer, sizeof(buffer), pipe))
        out += buffer;

    pclose(pipe);
    system("rm -f /tmp/gdb_cmds.txt");

    if (out.empty()) return "GDB_ERROR: no output";

    return cleangdb(out);  // clean before returning
}