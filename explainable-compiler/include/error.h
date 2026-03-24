#ifndef ERROR_H
#define ERROR_H

#include <string>
using namespace std;

struct errorobject
{
    string file;
    int line;
    int column;
    string type;
    string message;

    string category;
    string explanation;
    string fix;

    string tojson() const;
};

#endif