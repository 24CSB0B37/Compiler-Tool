#include "../include/parser.h"
#include <cstdio>

vector<errorobject> parseerrors(const string &output)
{
    vector<errorobject> errors;

    char linebuf[512];
    int i = 0;

    while (i < output.length())
    {
        int j = 0;

        while (i < output.length() && output[i] != '\n')
        {
            linebuf[j++] = output[i++];
        }

        linebuf[j] = '\0';
        i++;

        char file[100], type[20], msg[300];
        int l, c;

        if (sscanf(linebuf, "%[^:]:%d:%d: %[^:]: %[^\n]", file, &l, &c, type, msg) == 5)
        {
            errorobject e;
            e.file = file;
            e.line = l;
            e.column = c;
            e.type = type;
            e.message = msg;

            errors.push_back(e);
        }
    }

    return errors;
}