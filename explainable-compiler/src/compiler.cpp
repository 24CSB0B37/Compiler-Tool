#include "../include/compiler.h"
#include <cstdio>
#include <iostream>

using namespace std;

string runcompiler(const string &filename)
{
    string command;
    cout << "Running compiler on: " << filename << endl;

    // detect file type
    if (filename.find(".c") != string::npos)
        command = "gcc " + filename + " 2>&1";
    else
        command = "g++ " + filename + " 2>&1";

    string output = "";

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        cout << "Error running compiler\n";
        return "";
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        output += buffer;
    }

    pclose(pipe);
    return output;
}