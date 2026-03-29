#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include<unordered_map>
using namespace std;
// =====================
// SYMBOL TABLE
// =====================
using VarTable = unordered_map<string, double>;


// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Infix → Postfix (Shunting Yard)
vector<string> infixToPostfix(const string& expr) {
    stack<char> ops;
    vector<string> output;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // skip spaces
        if (isspace(c)) continue;

        // number (can be multi-digit or decimal)
        if (isdigit(c) || c == '.') {
            string num;
            while (i < expr.length() &&
                   (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                i++;
            }
            i--;
            output.push_back(num);
        }
        // VARIABLE
        else if (isalpha(c)) {
            string var;
            while (i < expr.length() && isalnum(expr[i])) {
                var += expr[i++];
            }
            i--;
            output.push_back(var);
        }
        // opening parenthesis
        else if (c == '(') {
            ops.push(c);
        }
        // closing parenthesis
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            if (!ops.empty())
                ops.pop(); // remove '('
        }
        // operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() &&
                   precedence(ops.top()) >= precedence(c)) {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push(c);
        }
    }

    while (!ops.empty()) {
        output.push_back(string(1, ops.top()));
        ops.pop();
    }

    return output;
}

/* Evaluate postfix expression
double evaluatePostfix(const vector<string>& postfix) {
    stack<double> st;

    for (const string& token : postfix) {
        if (isdigit(token[0]) || token[0] == '.') {
            st.push(stod(token));
        } else {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();

            switch (token[0]) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
            }
        }
    }
    return st.top();
}
*/

//NODE
struct Node {
    std::string value; // "3", "+", "*"
    Node* left;
    Node* right;

    Node(const std::string& v)
        : value(v), left(nullptr), right(nullptr) {}
};
// =====================
// BUILD TREE
// =====================
Node* buildTree(const vector<string>& postfix) {
    stack<Node*> st;

    for (const auto& token : postfix) {
        if (isdigit(token[0]) || isalpha(token[0])) {
            st.push(new Node(token));
        } else {
            Node* r = st.top(); st.pop();
            Node* l = st.top(); st.pop();

            Node* op = new Node(token);
            op->left = l;
            op->right = r;
            st.push(op);
        }
    }
    return st.top();
}

//-----------------------------------------
// =====================
// EVALUATE TREE
// =====================
double evaluate(Node* root, const VarTable& vars) {
    if (!root->left && !root->right) {
        if (isdigit(root->value[0]) || root->value[0] == '.')
            return stod(root->value);

        if (vars.count(root->value))
            return vars.at(root->value);

        throw runtime_error("Unknown variable: " + root->value);
    }

    double l = evaluate(root->left, vars);
    double r = evaluate(root->right, vars);

    if (root->value == "+") return l + r;
    if (root->value == "-") return l - r;
    if (root->value == "*") return l * r;
    if (root->value == "/") return l / r;

    throw runtime_error("Unknown operator");
}
//-----------------------------------------


//---------------------------------------
//CALCULATE
// =====================
// CALCULATE
// =====================
double calculate(const string& expr, const VarTable& vars) {
    auto postfix = infixToPostfix(expr);
    Node* root = buildTree(postfix);
    return evaluate(root, vars);
}
int main() {
    string expr;
    VarTable vars;

    vars["a"] = 5;
    vars["b"] = 3;
    vars["x"] = 10;
    vars["y"] = 2;
    cout << "INPUT EXPRESSION:\n";
    getline(cin, expr);

    double result = calculate(expr, vars);

    cout << "RESULT  = " << result << endl;

    return 0;
}
