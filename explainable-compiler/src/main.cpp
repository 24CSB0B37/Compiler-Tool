#include <iostream>
#include <fstream>
#include <vector>

#include "../include/compiler.h"
#include "../include/parser.h"
#include "../include/error.h"
#include "../include/explainer.h"

using namespace std;

// save JSON to file
void savejson(const vector<errorobject> &errors)
{
    system("mkdir -p output");
    ofstream fout("output/errors.json");

    fout << "[\n";

    for (int i = 0; i < errors.size(); i++)
    {
        fout << "  " << errors[i].tojson();

        if (i != errors.size() - 1)
            fout << ",";

        fout << "\n";
    }

    fout << "]\n";

    fout.close();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: ./compiler <filename>\n";
        return 0;
    }

    string filename = argv[1];

    string output = runcompiler(filename);

    cout << "\n--- Raw Compiler Output ---\n";
    cout << output << endl;

    vector<errorobject> errors = parseerrors(output);
    generateexplanations(errors);

    cout << "\n--- Parsed Errors ---\n";
    for (auto &e : errors)
    {
        cout << e.file << ":" << e.line << ":" << e.column
             << " -> " << e.message << endl;
    }

    savejson(errors);

    cout << "\nJSON saved to output/errors.json\n";

    return 0;
}