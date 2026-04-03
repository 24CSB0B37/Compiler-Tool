#include <iostream>
#include <fstream>
#include <vector>

#include "../include/compiler.h"
#include "../include/parser.h"
#include "../include/explainer.h"
#include "../include/runtime.h"
#include "../include/debugger.h"
#include "../include/chat.h"
#include "../include/hf.h"

using namespace std;

void save(vector<errorobject> &errors)
{
    system("mkdir -p output");
    ofstream f("output/errors.json");
    f << "[\n";
    for (int i = 0; i < errors.size(); i++)
    {
        f << errors[i].tojson();
        if (i != errors.size() - 1) f << ",";
        f << "\n";
    }
    f << "]";
}

int main()
{
    string file;
    cout << "Enter file: ";
    cin >> file;

    cout << "[1] Running compiler..." << endl;
    string comp = runcompiler(file);
    cout << "[2] Compiler output: " << comp << endl;

    FILE *f = fopen("./program", "r");
    bool compiled = (f != nullptr);
    if (f) fclose(f);

    vector<errorobject> errors = parseerrors(comp);
    explain(errors);

    if (!compiled)
    {
        cout << "[!] Compile failed, skipping runtime" << endl;
        if (!errors.empty())
        {
            string p = prompt(errors[0], file);
            cout << "\nAI:\n" << hf(p) << endl;
        }
        save(errors);
        return 0;
    }

    cout << "[5] Running program..." << endl;
    string r = runprog();
    cout << "[6] Runtime output: " << r << endl;

    if (r.find("SIGNAL")            != string::npos ||
    r.find("Segmentation fault") != string::npos ||
    r.find("TIMEOUT")           != string::npos ||
    r.find("core dumped")       != string::npos ||
    r.find("EXIT_CODE:139")     != string::npos ||  // segfault exit code
    r.find("EXIT_CODE:136") != string::npos)    // floating point exception exit code
    {
        cout << "[7] Crash detected, running GDB..." << endl;
        errorobject e;
        e.runtime_error = "Runtime Crash Detected";
        e.runtime_trace = gettrace();

        // log what GDB actually returned
        if (e.runtime_trace.find("GDB_ERROR") != string::npos)
            cout << "[GDB] Failed: " << e.runtime_trace << endl;
        else if (e.runtime_trace.find("GDB_WARNING") != string::npos)
            cout << "[GDB] Warning: " << e.runtime_trace << endl;
        else
            cout << "[GDB] Success - trace captured" << endl;

        errors.push_back(e);
        cout << "[8] GDB done" << endl;
    }

    if (!errors.empty())
    {
        cout << "[9] Calling AI..." << endl;
        string p = prompt(errors[0], file);
        cout << "\nAI:\n" << hf(p) << endl;
    }

    save(errors);
    cout << "[10] Saved to output/errors.json" << endl;
}