#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "error.h"

using namespace std;

vector<errorobject> parseerrors(const string &output);

#endif