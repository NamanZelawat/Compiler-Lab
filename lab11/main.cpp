#include <bits/stdc++.h>
using namespace std;

map<char, int> State = {
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'a', 10},
    {'b', 11}
};

map<int, char> RevState = {
    {1, '1'}, 
    {2, '2'},
    {3, '3'},
    {4, '4'}, 
    {5, '5'},
    {6, '6'},
    {7, '7'},
    {8, '8'},
    {9, '9'},
    {10, 'a'},
    {11, 'b'}
};

map<int, string> productions = {
    {1, "E/E+T"},
    {2, "E/T"},
    {3, "T/T*F"},
    {4, "T/F"},
    {5, "F/(E)"},
    {6, "F/i"}
};

map<pair<int, char>, string> Action = {
    {{0, 'i'}, "s5"}, {{0, '+'}, "e1"}, {{0, '*'}, "e1"}, {{0, '('}, "s4"}, {{0, ')'}, "e2"}, {{0, '$'}, "e1"},
    {{1, 'i'}, "e3"}, {{1, '+'}, "s6"}, {{1, '*'}, "e1"}, {{1, '('}, "e3"}, {{1, ')'}, "e2"}, {{1, '$'}, "acc"},
    {{2, 'i'}, "e3"}, {{2, '+'}, "r2"}, {{2, '*'}, "s7"}, {{2, '('}, "e3"}, {{2, ')'}, "r2"}, {{2, '$'}, "r2"},
    {{3, 'i'}, "e3"}, {{3, '+'}, "r4"}, {{3, '*'}, "r4"}, {{3, '('}, "e3"}, {{3, ')'}, "r4"}, {{3, '$'}, "r4"},
    {{4, 'i'}, "s5"}, {{4, '+'}, "e1"}, {{0, '*'}, "e1"}, {{0, '('}, "s4"}, {{0, ')'}, "e2"}, {{0, '$'}, "e1"},
    {{5, 'i'}, "e3"}, {{5, '+'}, "r6"}, {{5, '*'}, "r6"}, {{5, '('}, "e3"}, {{5, ')'}, "r6"}, {{5, '$'}, "r6"},
    {{6, 'i'}, "s5"}, {{6, '+'}, "e1"}, {{6, '*'}, "e1"}, {{6, '('}, "s4"}, {{6, ')'}, "e2"}, {{6, '$'}, "e1"},
    {{7, 'i'}, "s5"}, {{7, '+'}, "e1"}, {{7, '*'}, "e1"}, {{7, '('}, "s4"}, {{7, ')'}, "e2"}, {{7, '$'}, "e1"},
    {{8, 'i'}, "e3"}, {{8, '+'}, "s6"}, {{8, '*'}, "e1"}, {{8, '('}, "e3"}, {{8, ')'}, "s11"}, {{8, '$'}, "e4"},
    {{9, 'i'}, "e3"}, {{9, '+'}, "r1"}, {{9, '*'}, "s7"}, {{9, '('}, "e3"}, {{9, ')'}, "r1"}, {{9, '$'}, "r1"},
    {{10, 'i'}, "e3"}, {{10, '+'}, "r3"}, {{10, '*'}, "r3"}, {{10, '('}, "e3"}, {{10, ')'}, "r3"}, {{10, '$'}, "r3"},
    {{11, 'i'}, "e3"}, {{11, '+'}, "r5"}, {{11, '*'}, "r5"}, {{11, '('}, "e3"}, {{11, ')'}, "r5"}, {{11, '$'}, "r5"}
};

map<pair<int, char>, int> Goto = {
    {{0, 'E'}, 1}, {{0, 'T'}, 2}, {{0, 'F'}, 3}, 
    {{1, 'E'}, -1}, {{1, 'T'}, -1}, {{1, 'F'}, -1}, 
    {{2, 'E'}, -1}, {{2, 'T'}, -1}, {{2, 'F'}, -1}, 
    {{3, 'E'}, -1}, {{3, 'T'}, -1}, {{3, 'F'}, -1}, 
    {{4, 'E'}, 8}, {{4, 'T'}, 2}, {{4, 'F'}, 3}, 
    {{5, 'E'}, -1}, {{5, 'T'}, -1}, {{5, 'F'}, -1},
    {{6, 'E'}, -1}, {{6, 'T'}, 9}, {{6, 'F'}, 3},
    {{7, 'E'}, -1}, {{7, 'T'}, -1}, {{7, 'F'}, 10},
    {{8, 'E'}, -1}, {{8, 'T'}, -1}, {{8, 'F'}, -1},
    {{9, 'E'}, -1}, {{9, 'T'}, -1}, {{9, 'F'}, -1},
    {{10, 'E'}, -1}, {{10, 'T'}, -1}, {{10, 'F'}, -1},
    {{11, 'E'}, -1}, {{11, 'T'}, -1}, {{11, 'F'}, -1}
}; 

void printStack(stack<char> parser) {
    cout << "Stack: ";
    while(!parser.empty()) {
        cout << parser.top() << " ";
        parser.pop();
    }

    cout << endl;
}

bool parse(string test) {
    stack<char> parser;
    parser.push('$');
    test += '$';

    int idx = 0;
    parser.push('0');

    cout << "test: " << test << endl;
    // printStack(parser);
    while(test[idx] != '$' || parser.top() != '$') {

        int state = State[parser.top()];
        string act = Action[{state, test[idx]}];
        if(act == "e1") {
            char new_state = '3';
            parser.push('i');
            parser.push(new_state);
            cout << "Error: Missing operand\n";
        }
        else if(act=="e2")
        {
            idx++;
            cout << "Error: Unbalanced Right Parenthesis\n";
        }
        else if(act=="e3")
        {
            char new_state = '6';
            parser.push('+');
            parser.push(new_state);
            cout << "Error: Missing operator\n";
        }
        else if(act=="e4")
        {
            char new_state = '9';
            parser.push(')');
            parser.push(new_state);
            cout << "Error: Missing right parenthesis\n";
        }
        else if(act[0] == 's') {
            char new_state = act[1];
            parser.push(test[idx]);
            idx++;
            parser.push(new_state);
            cout << "Shift Operation -- "<<new_state<<endl;
        } else {
            int prod_num = act[1] - '0';
            string right_side = productions[prod_num].substr(2);
            char left_side = productions[prod_num][0];
            while(parser.top() != right_side[0]) {
                parser.pop();
            }
            cout << "left: " << left_side << " right: " << right_side << endl;
            parser.pop();
            int temp_state = State[parser.top()];
            parser.push(left_side);
            int next_state = Goto[{temp_state, left_side}];
            cout << "temp_state: " << temp_state << " next_state: " << next_state << endl;
            parser.push(RevState[next_state]);
            //cout << "prod_num: " << prod_num << endl;
            cout << "Reduce by " << productions[prod_num] << endl;
        }

        //printStack(parser);
    }

    if(parser.top() == '1') return true;
    return false;
}

int main() {

    string test;
    cout << "Enter string to test: ";
    cin >> test;

    bool accepted = parse(test);
    if(accepted) cout << "String Accepted\n";
    else cout << "Not Accepted\n";
    return 0;
}

/*
i*i+i
i*i+i*i
i+i*i+i
*/
