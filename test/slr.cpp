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
    {5, "F/(i)"},
    {6, "F/i"}
};

map<pair<int, char>, string> Action = {
    {{0, 'i'}, "s5"}, {{0, '+'}, ""}, {{0, '*'}, ""}, {{0, '('}, "s4"}, {{0, ')'}, ""}, {{0, '$'}, ""},
    {{1, 'i'}, ""}, {{1, '+'}, "s6"}, {{1, '*'}, ""}, {{1, '('}, ""}, {{1, ')'}, ""}, {{1, '$'}, "acc"},
    {{2, 'i'}, ""}, {{2, '+'}, "r2"}, {{2, '*'}, "s7"}, {{2, '('}, ""}, {{2, ')'}, "r2"}, {{2, '$'}, "r2"},
    {{3, 'i'}, ""}, {{3, '+'}, "r4"}, {{3, '*'}, "r4"}, {{3, '('}, ""}, {{3, ')'}, "r4"}, {{3, '$'}, "r4"},
    {{4, 'i'}, "s5"}, {{4, '+'}, ""}, {{0, '*'}, ""}, {{0, '('}, "s4"}, {{0, ')'}, ""}, {{0, '$'}, ""},
    {{5, 'i'}, ""}, {{5, '+'}, "r6"}, {{5, '*'}, "r6"}, {{5, '('}, ""}, {{5, ')'}, "r6"}, {{5, '$'}, "r6"},
    {{6, 'i'}, "s5"}, {{6, '+'}, ""}, {{6, '*'}, ""}, {{6, '('}, "s4"}, {{6, ')'}, ""}, {{6, '$'}, ""},
    {{7, 'i'}, "s5"}, {{7, '+'}, ""}, {{7, '*'}, ""}, {{7, '('}, "s4"}, {{7, ')'}, ""}, {{7, '$'}, ""},
    {{8, 'i'}, ""}, {{8, '+'}, "s6"}, {{8, '*'}, ""}, {{8, '('}, "s4"}, {{8, ')'}, "s11"}, {{8, '$'}, ""},
    {{9, 'i'}, ""}, {{9, '+'}, "r1"}, {{9, '*'}, "s7"}, {{9, '('}, ""}, {{9, ')'}, "r1"}, {{9, '$'}, "r1"},
    {{10, 'i'}, ""}, {{10, '+'}, "r3"}, {{10, '*'}, "r3"}, {{10, '('}, ""}, {{10, ')'}, "r3"}, {{10, '$'}, "r3"},
    {{11, 'i'}, ""}, {{11, '+'}, "r5"}, {{11, '*'}, "r5"}, {{11, '('}, ""}, {{11, ')'}, "r5"}, {{11, '$'}, "r5"}
};

map<pair<int, char>, int> Goto = {
    {{0, 'E'}, 1}, {{0, 'T'}, 2}, {{0, 'F'}, 3}, 
    {{1, 'E'}, -1}, {{1, 'T'}, -1}, {{1, 'F'}, -1}, 
    {{2, 'E'}, -1}, {{2, 'T'}, -1}, {{2, 'F'}, -1}, 
    {{3, 'E'}, -1}, {{3, 'T'}, -1}, {{3, 'F'}, -1}, 
    {{4, 'E'}, 8}, {{4, 'T'}, 2}, {{0, 'F'}, 3}, 
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

    //cout << "test: " << test << endl;
    //printStack(parser);
    while(parser.top() != '1' && test[idx] != '$') {

        int state = State[parser.top()];
        string act = Action[{state, test[idx]}];
        if(act == "") {
            return 0;
        } else if(act[0] == 's') {
            char new_state = act[1];
            parser.push(test[idx]);
            idx++;
            parser.push(new_state);
            cout << "Shift Operation\n";
        } else {
            int prod_num = act[1] - '0';
            string right_side = productions[prod_num].substr(2);
            char left_side = productions[prod_num][0];
            while(parser.top() != right_side[0]) {
                parser.pop();
            }
            //cout << "left: " << left_side << " right: " << right_side << endl;
            parser.pop();
            int temp_state = State[parser.top()];
            parser.push(left_side);
            int next_state = Goto[{temp_state, left_side}];
            //cout << "temp_state: " << temp_state << " next_state: " << next_state << endl;
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
