#include "../include/error.h"

// string errorobject::tojson() const
// {
//     string json = "{";
//     json += "\"file\": \"" + file + "\", ";
//     json += "\"line\": " + to_string(line) + ", ";
//     json += "\"column\": " + to_string(column) + ", ";
//     json += "\"type\": \"" + type + "\", ";
//     json += "\"message\": \"" + message + "\"";
//     json += "}";
//     return json;
// }

string errorobject::tojson() const
{
    string json = "{";
    json += "\"file\": \"" + file + "\", ";
    json += "\"line\": " + to_string(line) + ", ";
    json += "\"column\": " + to_string(column) + ", ";
    json += "\"type\": \"" + type + "\", ";
    json += "\"message\": \"" + message + "\", ";
    json += "\"category\": \"" + category + "\", ";
    json += "\"explanation\": \"" + explanation + "\", ";
    json += "\"fix\": \"" + fix + "\"";
    json += "}";
    return json;
}