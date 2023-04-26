#include <iostream>
#include <string>
#include <vector>
using namespace std;

int get_precedence(char op)
{
    if (op == '!')
    {
        return 3;
    }
    else if (op == '&')
    {
        return 2;
    }
    else if (op == '|')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool evaluate_expressionession(const  string &expression, const  vector<bool> &values) {
    vector<bool> result;
    for (char c : expression)
        {
            if (c >= 'A' && c <= 'D')
            {
            result.push_back(values[c - 'A']);
            }
            else if (c == '&')
            {
                bool a = result.back(); result.pop_back();
                bool b = result.back(); result.pop_back();
                result.push_back(a && b);
            }
            else if (c == '|')
            {
                bool a = result.back(); result.pop_back();
                bool b = result.back(); result.pop_back();
                result.push_back(a || b);
            }
            else if (c == '!')
            {
                bool a = result.back(); result.pop_back();
                result.push_back(!a);
            }
        }
        return result.back();
    }

string infix_to_postfix(const  string &infix)
{
    string postfix;
    vector<char> op_stack;

    for (char c : infix)
        {
            if (c >= 'A' && c <= 'D')
            {
                postfix += c;
            }
            else if (c == '(')
            {
                op_stack.push_back(c);
            }
            else if (c == ')')
            {
            while (!op_stack.empty() && op_stack.back() != '(')
            {
                postfix += op_stack.back();
                op_stack.pop_back();
            }
            op_stack.pop_back(); // Remove the '('
            }
            else if (c == '&' || c == '|' || c == '!')
            {
            while (!op_stack.empty() && get_precedence(op_stack.back()) >= get_precedence(c) && op_stack.back() != '(')
            {
                postfix += op_stack.back();
                op_stack.pop_back();
            }
            op_stack.push_back(c);
        }
    }

    while (!op_stack.empty())
    {
    postfix += op_stack.back();
    op_stack.pop_back();
    }
    return postfix;
}

int main()
{
    string expression;
    cout << "Enter the expression (use A, B, C, D for variables, & for AND, | for OR, ! for NOT): ";
    getline(cin, expression);

    string postfix_expression = infix_to_postfix(expression);
    vector<char> variables;
    for (char c : expression)
        {
            if (c >= 'A' && c <= 'D')
            {
                bool found = false;
                for (char var : variables)
                {
                    if (var == c)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    variables.push_back(c);
                }
            }
        }

    for (char c : variables)
        {
        cout << c << " ";
        }
        cout << "Result\n";

    for (int i = 0; i < (1 << variables.size()); ++i)
    {
        vector<bool> values(variables.size());
        for (int j = 0; j < variables.size(); ++j)
        {
            values[j] = (i & (1 << j)) != 0;
            cout << values[j] << " ";
        }
        cout << evaluate_expressionession(postfix_expression, values) << "\n";
    }
    return 0;
}
