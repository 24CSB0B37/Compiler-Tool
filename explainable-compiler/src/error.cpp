#include "../include/error.h"

string escapefield(const string &s)
{
    string out;
    for (char c : s)
    {
        if (c == '\"') out += "'";
        else if (c == '\\') out += "/";
        else if (c == '\n') out += ' ';
        else if (c == '\t') out += ' ';
        else if (c == '\r') continue;
        else out += c;
    }
    return out;
}

string errorobject::tojson() const
{
    string json = "{";
    json += "\"file\": \""         + escapefield(file)          + "\", ";
    json += "\"line\": "           + to_string(line)            + ", ";
    json += "\"column\": "         + to_string(column)          + ", ";
    json += "\"type\": \""         + escapefield(type)          + "\", ";
    json += "\"message\": \""      + escapefield(message)       + "\", ";
    json += "\"category\": \""     + escapefield(category)      + "\", ";
    json += "\"explanation\": \""  + escapefield(explanation)   + "\", ";
    json += "\"fix\": \""          + escapefield(fix)           + "\", ";
    json += "\"runtime_error\": \" "+ escapefield(runtime_error)+ "\", ";
    json += "\"runtime_trace\": \" "+ escapefield(runtime_trace)+ "\"";
    json += "}";
    return json;
}