#include "../include/hf.h"
#include <cstdio>
#include <fstream>

string escape_json(const string &s)
{
    string out;
    for (char c : s)
    {
        if (c == '\"') out += "\\\"";
        else if (c == '\\') out += "/";
        else if (c == '\n') out += ' ';
        else if (c == '\r') continue;
        else if (c == '\t') out += ' ';
        else out += c;
    }
    return out;
}

string getapikey()
{
    ifstream f(".env");
    if (!f.is_open()) return "";
    string line;
    while (getline(f, line))
    {
        if (line.find("GROQ_API_KEY=") == 0)
            return line.substr(13);
    }
    return "";
}

string clean_output(const string &s)
{
    string out;
    bool skip = false;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '`') { skip = !skip; continue; }
        if (skip) continue;
        if (s[i] == '*') continue;
        if (s[i] == '#') continue;
        if (s[i] == '\\' && i+1 < s.size() && s[i+1] == 'n')
        { out += ' '; i++; continue; }
        out += s[i];
        if (s[i] == '.' && i+1 < s.size() && s[i+1] == ' '){
                out += '\n';
                i++;    
        }
    }
    size_t cut = out.find("Here's");
    if (cut == string::npos) cut = out.find("here's");
    if (cut == string::npos) cut = out.find("corrected code");
    if (cut == string::npos) cut = out.find("Here is");
    if (cut != string::npos) out = out.substr(0, cut);
    return out;
}

string hf(const string &p)
{
    string safe = escape_json(p);
    string API_KEY = getapikey();
    if (API_KEY.empty()) return "AI failed: no API key found";

    string cmd =
        "curl -s -X POST https://api.groq.com/openai/v1/chat/completions "
        "-H \"Authorization: Bearer " + API_KEY + "\" "
        "-H \"Content-Type: application/json\" "
        "-d '{\"model\":\"llama-3.1-8b-instant\","
        "\"messages\":[{\"role\":\"system\",\"content\":\"You are a C++ debugger. Explain the bug and give fix within 500 words. State: 1) what the bug is 2) why and where it crashes 3) how to fix it. No markdown, no code blocks, plain text only.\"},"
        "{\"role\":\"user\",\"content\":\"" + safe + "\"}],"
        "\"max_tokens\":1024}'";

    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "AI failed";

    char buffer[512];
    string out;
    while (fgets(buffer, sizeof(buffer), pipe))
        out += buffer;
    pclose(pipe);

    size_t pos = out.find("\"content\"");
    if (pos != string::npos)
    {
        size_t start = out.find(":", pos) + 2;
        size_t end = out.find("\"", start);
        return clean_output(out.substr(start, end - start));
    }

    return out;
}