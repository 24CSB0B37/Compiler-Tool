#include "../include/chat.h"
#include <fstream>
#include <sstream>

string readfile(const string &path)
{
    ifstream f(path);
    if (!f.is_open()) return "";
    stringstream ss;
    ss << f.rdbuf();
    string content = ss.str();
    if (content.size() > 5000) content = content.substr(0, 5000);
    return content;
}

string cleantrace(const string &trace)
{
    // extract only useful lines from gdb output
    string out;
    istringstream ss(trace);
    string line;
    while (getline(ss, line))
    {
        // keep only backtrace, locals, source lines
        if (line.find("#")        != string::npos ||
            line.find("at ")      != string::npos ||
            line.find("line ")    != string::npos ||
            line.find("= ")       != string::npos ||
            line.find("signal")   != string::npos ||
            line.find("main")     != string::npos)
        {
            out += line + " ";
        }
    }
    if (out.size() > 500) out = out.substr(0, 500);
    return out;
}

string prompt(const errorobject &e, const string &filepath)
{
    string code = readfile(filepath);
    string p = "You are a C++ debugger. Explain the bug and give a fix within 500 words and be concise while also mentioning the error type, line numbers, etc. (Technical terms allowed). ";

    if (!code.empty())
        p += "Code: " + code + " ";

    if (!e.message.empty() && e.runtime_error.empty())
    {
        p += "Compile error: " + e.message + " ";
        if (!e.category.empty())
            p += "Category: " + e.category + " ";
    }

    if (!e.runtime_error.empty())
    {
        p += "Runtime crash: " + e.runtime_error + " ";
        if (!e.runtime_trace.empty())
        {
            string trace = cleantrace(e.runtime_trace);
            if (!trace.empty())
                p += "GDB info: " + trace + " ";
        }
    }

    return p;
}
