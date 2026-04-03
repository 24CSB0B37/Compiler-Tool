#include "../include/compiler.h"
#include <cstdio>

string runcompiler(const string &file)
{
    // delete old binary first
    system("rm -f ./program");

    string cmd;

    if (file.size() >= 2 && file.substr(file.size() - 2) == ".c")
        cmd = "gcc -g " + file + " -o program 2>&1";
    else
        cmd = "g++ -g " + file + " -o program 2>&1";

    FILE *pipe = popen(cmd.c_str(), "r");
    char buffer[256];
    string output;

    while (fgets(buffer, sizeof(buffer), pipe))
        output += buffer;

    pclose(pipe);
    return output;
}