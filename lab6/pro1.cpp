#include<bits/stdc++.h>

using namespace std;

int main()
{
	map<char,int> terminal;
	terminal['#'] = 0;
	terminal['('] = 1;
	terminal[')'] = 2;
	terminal['+'] = 3;
	terminal['*'] = 4;
	terminal['$'] = 5;

	map<char,int> non_terminal;
	non_terminal['E'] = 0;
	non_terminal['P'] = 1;
	non_terminal['T'] = 2;
	non_terminal['C'] = 3;
	non_terminal['F'] = 4;

	map<int,string> production;
	production[1] = "TP";
	production[2] = "+TP";
	production[3] = "";
	production[4] = "FC";
	production[5] = "*FC";
	production[6] = "";
	production[7] = "(E)";
	production[8] = "#";

	int predi_parse_table[5][6] = {
		{1,1,-1,-1,-1,-1},
		{-1,-1,3,2,-1,3},
		{4,4,-1,-1,-1,-1},
		{-1,-1,6,6,5,6},
		{8,7,-1,-1,-1,-1}
	};

	string input;
	cin>>input;

	input.push_back('$');

	cout<<"Input Modified --> "<<input<<endl;

	stack<char> st;

	st.push('$');
	st.push('E');

	int i = 0;

	int cnt = 0;

	while(true)
	{
		char input_comp = input[i];
		char stack_comp = st.top();
		st.pop();

		if(input_comp == '$' && stack_comp == '$')
		{
			cout<<"Parsing successful\nBye\n";
			break;
		}

		if(input_comp == stack_comp)
		{
			i++;
			continue;
		}


		int prod = predi_parse_table[non_terminal[stack_comp]][terminal[input_comp]];

		if(prod == -1)
		{
			cout<<"ERROR\n";
			break;
		}

		for(int j = production[prod].size()-1;j>=0;j--)
		{
			st.push(production[prod][j]);
		}
	}
}