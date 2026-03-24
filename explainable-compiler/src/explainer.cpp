#include "../include/explainer.h"

void ai_enhance(errorobject &e)
{
    // future: call external API here

    if (e.category == "Unknown")
    {
        e.explanation += " (AI enhancement can provide more details here)";
        e.fix += " (AI can suggest a better fix)";
    }
}

void generateexplanations(vector<errorobject> &errors)
{
    for (auto &e : errors)
    {
        string msg = e.message;

        // Rule 1: Missing semicolon
        if (msg.find("expected ';'") != string::npos)
        {
            e.category = "Syntax Error";
            e.explanation = "A semicolon is required to terminate a statement in C/C++.";
            e.fix = "Add ';' at the end of the statement.";
        }

        // Rule 2: Undeclared variable
        else if (msg.find("not declared") != string::npos)
        {
            e.category = "Semantic Error";
            e.explanation = "The variable is used without being declared.";
            e.fix = "Declare the variable before using it.";
        }

        // Rule 3: Invalid conversion
        else if (msg.find("invalid conversion") != string::npos)
        {
            e.category = "Type Error";
            e.explanation = "There is a mismatch between expected and provided data types.";
            e.fix = "Ensure type compatibility or use casting.";
        }

        // Rule 4: Missing parenthesis
        else if (msg.find("expected ')'") != string::npos)
        {
            e.category = "Syntax Error";
            e.explanation = "A closing parenthesis is missing.";
            e.fix = "Add the missing ')'.";
        }

        // Default case
        else
        {
            e.category = "Unknown";
            e.explanation = "No detailed explanation available.";
            e.fix = "Refer to compiler message.";
        }

        //ai_enhance(e);
    }
}