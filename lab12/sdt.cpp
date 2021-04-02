#include<bits/stdc++.h>

using namespace std;

void infixToPostfix(string s)
{
	unordered_map<char,int>mp;
	mp['~']=4;
	mp['^']=3;
	mp['/']=mp['*']=2;
	mp['-']=mp['+']=1;
	stack<char> st;
	st.push('N');
	int n= s.length();
	string ns;
	for(int i = 0; i < n; i++)
	{
		if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		ns+=s[i];
		else if(s[i] == '(')
		st.push('(');
		else if(s[i] == ')')
		{
			while(st.top() != 'N' && st.top() != '(')
			{
				char c = st.top();
				st.pop();
				ns += c;
			}
			if(st.top() == '(')
			{
				char c = st.top();
				st.pop();
			}
		}
		else
		{
			while(st.top() != 'N' && mp[s[i]] <=mp[st.top()])
			{
				char c = st.top();
				st.pop();
				ns += c;
			}
			st.push(s[i]);
		}

	}
	while(st.top() != 'N')
	{
		char c = st.top();
		st.pop();
		ns += c;
	}
	cout << ns << endl;
}

int main()
{
	string s;
	cout<<"INPUT : \n";
	cin>>s;
	cout<<"Postfix Expression:";
	infixToPostfix(s);
	return 0;
}

