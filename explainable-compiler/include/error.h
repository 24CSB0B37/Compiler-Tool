#ifndef ERROR_H
#define ERROR_H

#include <string>
using namespace std;

struct errorobject
{
    string file;
    int line = 0;
    int column = 0;
    string type;
    string message;

    string category;
    string explanation;
    string fix;

    string runtime_error;
    string runtime_trace;

    string tojson() const;
};

#endif