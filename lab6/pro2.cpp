#include<bits/stdc++.h>

using namespace std;

int main()
{
	map<char,int> terminal;
	terminal['a'] = 0;
	terminal['b'] = 1;
	terminal['d'] = 2;
	terminal['f'] = 3;
	terminal['g'] = 4;
	terminal['$'] = 5;

	map<char,int> non_terminal;
	non_terminal['S'] = 0;
	non_terminal['A'] = 1;
	non_terminal['B'] = 2;
	non_terminal['C'] = 3;
	non_terminal['D'] = 4;

	map<int,string> production;
	production[1] = "A";
	production[2] = "aB";
	production[3] = "dD";
	production[4] = "bBC";
	production[5] = "f";
	production[6] = "g";
	production[7] = "dD";
	production[8] = "";

	int predi_parse_table[5][7] = {
		{1,-1,1,-1,-1,-1},
		{2,-1,3,-1,-1,-1},
		{-1,4,-1,5,-1,-1},
		{-1,-1,-1,-1,6,-1},
		{-1,-1,7,-1,-1,8}
	};

	string input;
	cin>>input;

	input.push_back('$');

	cout<<"Input Modified --> "<<input<<endl;

	stack<char> st;

	st.push('$');
	st.push('S');

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