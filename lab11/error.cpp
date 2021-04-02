#include <bits/stdc++.h>

using namespace std;

map<pair<int,char>,string> Action=
{ {{0, 'i'}, "s3"}, {{0, '+'}, "e1"}, {{0, '*'}, "e1"}, {{0, '('}, "s2"}, {{0, ')'}, "e2"}, {{0, '$'}, "e1"},
{{1, 'i'}, "e3"}, {{1, '+'}, "s4"}, {{1, '*'}, "s5"}, {{1, '('}, "e3"}, {{1, ')'}, "e2"}, {{1, '$'}, "acc"},
{{2, 'i'}, "s3"}, {{2, '+'}, "e1"}, {{2, '*'}, "e1"}, {{2, '('}, "s2"}, {{2, ')'}, "e2"}, {{2, '$'}, "e1"},
{{3, 'i'}, "r4"}, {{3, '+'}, "r4"}, {{3, '*'}, "r4"}, {{3, '('}, "r4"}, {{3, ')'}, "r4"}, {{3, '$'}, "r4"},
{{4, 'i'}, "s3"}, {{4, '+'}, "e1"}, {{0, '*'}, "e1"}, {{0, '('}, "s2"}, {{0, ')'}, "e2"}, {{0, '$'}, "e1"},
{{5, 'i'}, "s3"}, {{5, '+'}, "e1"}, {{5, '*'}, "e1"}, {{5, '('}, "s2"}, {{5, ')'}, "e2"}, {{5, '$'}, "e1"},
{{6, 'i'}, "e3"}, {{6, '+'}, "s4"}, {{6, '*'}, "s5"}, {{6, '('}, "e3"}, {{6, ')'}, "s9"}, {{6, '$'}, "e4"},
{{7, 'i'}, "r1"}, {{7, '+'}, "r1"}, {{7, '*'}, "s5"}, {{7, '('}, "r1"}, {{7, ')'}, "r1"}, {{7, '$'}, "r1"},
{{8, 'i'}, "r2"}, {{8, '+'}, "r2"}, {{8, '*'}, "r2"}, {{8, '('}, "r2"}, {{8, ')'}, "r2"}, {{8, '$'}, "r2"},
{{9, 'i'}, "r3"}, {{9, '+'}, "r3"}, {{9, '*'}, "r3"}, {{9, '('}, "r3"}, {{9, ')'}, "r3"}, {{9, '$'}, "r3"}};

map<pair<int, char>, int> Goto = {
{{0, 'E'}, 1},
{{1, 'E'}, -1},
{{2, 'E'}, 6},
{{3, 'E'}, -1},
{{4, 'E'}, 7},
{{5, 'E'}, 8},
{{6, 'E'}, -1},
{{7, 'E'}, -1},
{{8, 'E'}, -1},
{{9, 'E'}, -1},
};

map<char, int> State = {
    {'1', 1},{'2', 2},{'3', 3},{'4', 4},{'5', 5},{'6', 6},{'7', 7},{'8', 8},{'9', 9}
};

map<int, char> RevState = {
    {1, '1'},{2, '2'},{3, '3'},{4, '4'},{5, '5'},{6, '6'},{7, '7'},{8, '8'},{9, '9'}
};

map<int, string> productions = {
    {1, "E/E+E"},{2, "E/E*E"},{3, "E/(E)"},{4, "E/i"}
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


    while(!(parser.top() == '1' && test[idx] == '$')) {

        int state = State[parser.top()];
        string act = Action[{state, test[idx]}];
        if(act == "e1") {

            char new_state = '3';
            parser.push('i');
            parser.push(new_state);
            cout<<"---------ERROR------------\n";
            cout << "Missing operand\n";
            cout<<"---------------------\n";
        }
        else if(act=="e2")
        {
            idx++;
             cout<<"---------ERROR------------\n";
            cout << "Unbalanced Parenthesis Right\n";
            cout<<"---------------------\n";
        }
        else if(act=="e3")
        {
            char new_state = '4';
            parser.push('+');
            parser.push(new_state);
             cout<<"---------ERROR------------\n";
            cout << "Missing operator\n";
            cout<<"---------------------\n";
        }
        else if(act=="e4")
        {
            char new_state = '9';
            parser.push(')');
            parser.push(new_state);
             cout<<"---------ERROR------------\n";
            cout << "Missing right parenthesis\n";
            cout<<"---------------------\n";
        }
        else if(act[0] == 's') {
            char new_state = act[1];
            parser.push(test[idx]);
            idx++;
            parser.push(new_state);
            cout<<"---------------------\n";
            cout << "Shift Operation -- "<<new_state<<endl;
            cout<<"---------------------\n";
        } else {
            int prod_num = act[1] - '0';
            string right_side = productions[prod_num].substr(2);
            char left_side = productions[prod_num][0];
            if(prod_num==4)
            {
                parser.pop();
                parser.pop();
            }
            else
            {
                for(int i=0;i<6;i++)
                parser.pop();
            }

            int temp_state = State[parser.top()];
            parser.push(left_side);
            int next_state = Goto[{temp_state, left_side}];

            parser.push(RevState[next_state]);
            cout<<"---------------------\n";
           cout << "Reduce by " << productions[prod_num] << endl;
           cout<<"---------------------\n";
        }

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