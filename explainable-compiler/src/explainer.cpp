#include "../include/explainer.h"

void explain(vector<errorobject> &errors)
{
    for (auto &e : errors)
    {
        string m = e.message;

        if (m.find("expected ';'") != string::npos)
        {
            e.category = "Syntax Error";
            e.explanation = "Missing semicolon.";
            e.fix = "Add ';'.";
        }
        else if (m.find("not declared") != string::npos)
        {
            e.category = "Semantic Error";
            e.explanation = "Variable not declared.";
            e.fix = "Declare it.";
        }
        else
        {
            e.category = "Unknown";
            e.explanation = "Refer compiler message.";
            e.fix = "Check syntax.";
        }
    }
}