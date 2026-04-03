#include "../include/parser.h"
#include <cstdio>

vector<errorobject> parseerrors(const string &out)
{
    vector<errorobject> errors;

    char file[100], type[20], msg[300];
    int l, c;

    char line[512];
    int i = 0;

    while (i < out.length())
    {
        int j = 0;
        while (i < out.length() && out[i] != '\n')
            line[j++] = out[i++];

        line[j] = '\0';
        i++;

        if (sscanf(line, "%[^:]:%d:%d: %[^:]: %[^\n]", file, &l, &c, type, msg) == 5)
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