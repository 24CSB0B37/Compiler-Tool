#include "../include/runtime.h"
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>

string runprog()
{
    FILE *pipe = popen("ulimit -s 8192; timeout 15 ./program 2>&1", "r");

    if (!pipe) return "popen failed";

    char buffer[256];
    string out;

    while (fgets(buffer, sizeof(buffer), pipe))
        out += buffer;

    int status = pclose(pipe);

    if (WIFEXITED(status))
    {
        int code = WEXITSTATUS(status);
        if (code != 0)
            out += "\nEXIT_CODE:" + to_string(code);
    }

    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        out += "\nSIGNAL:" + to_string(sig);

        if (sig == 11) out += " (Segmentation Fault)";
        else if (sig == 8)  out += " (Floating Point Exception)";
        else if (sig == 6)  out += " (Abort)";
        else if (sig == 9)  out += " (Killed)";
    }

    return out;
}