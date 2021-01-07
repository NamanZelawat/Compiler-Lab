#include<bits/stdc++.h>

using namespace std;

int machine(string &s,int &cnt)
{
	int i = 0;
	int state = 0;
	while(i<(cnt+1))
	{
		cout<<state<<((i == cnt)?("\n"):(" --> "));
		switch(state)
		{
			case 0:
				if(s[i] == 'B')
				{
					state = 1;
				}
				else if(s[i] == 'E')
				{
					state = 7;
				}
				else if(s[i] == 'I')
				{
					state = 15;
				}
				else if(s[i] == 'T')
				{
					state = 18;
				}
				else if(isalpha(s[i]))
				{
					state = 23;
				}
				else 
				{
					return -1;
				}
				break;
			case 1:
				if(s[i] == 'E')
				{
					state = 2;
				}
				else
				{
					state = 23;
				}
				break;
			case 2:
				if(s[i] == 'G')
				{
					state = 3;
				}
				else
				{
					state = 23;
				}
				break;
			case 3:
				if(s[i] == 'I')
				{
					state = 4;
				}
				else
				{
					state = 23;
				}
				break;
			case 4:
				if(s[i] == 'N')
				{
					state = 5;
				}
				else
				{
					state = 23;
				}
				break;
			case 5:
				if(s[i] == '\n' || s[i] == ' ')
				{
					state = 6;
				}
				else
				{
					state = 23;
				}
				break;
			case 6:
				return 1;
			case 7:
				if(s[i] == 'N')
				{
					state = 8;
				}
				else if(s[i] == 'L')
				{
					state = 11;
				}
				else
				{
					state = 23;
				}
				break;
			case 8:
				if(s[i] == 'D')
				{
					state = 9;
				}
				else
				{
					state = 23;
				}
				break;
			case 9:
				if(s[i] == '\n' || s[i] == ' ')
				{
					state = 10;
				}
				else
				{
					state = 23;
				}
				break;
			case 10:
				return 2;
			case 11:
				if(s[i] == 'S')
				{
					state = 12;
				}
				else
				{
					state = 23;
				}
				break;
			case 12:
				if(s[i] == 'E')
				{
					state = 13;
				}
				else
				{
					state = 23;
				}
				break;
			case 13:
				if(s[i] == '\n' || s[i] == ' ')
				{
					state = 14;
				}
				else
				{
					state = 23;
				}
				break;
			case 14:
				return 5;
			case 15:
				if(s[i] == 'F')
				{
					state = 16;
				}
				else
				{
					state = 23;
				}
				break;
			case 16:
				if(s[i] == '\n' || s[i] == ' ')
				{
					state = 17;
				}
				else
				{
					state = 23;
				}
				break;
			case 17:
				return 3;
			case 18:
				if(s[i] == 'H')
				{
					state = 19;
				}
				else
				{
					state = 23;
				}
				break;
			case 19:
				if(s[i] == 'E')
				{
					state = 20;
				}
				else
				{
					state = 23;
				}
				break;
			case 20:
				if(s[i] == 'N')
				{
					state = 21;
				}
				else
				{
					state = 23;
				}
				break;
			case 21:
				if(s[i] == '\n' || s[i] == ' ')
				{
					state = 22;
				}
				else
				{
					state = 23;
				}
				break;
			case 22:
				return 4;
			case 23:
				if(isalpha(s[i]) || (s[i]-'0' >= 0 && s[i] - '0' <= 9))
				{
					state = 23;
				}
				else if(s[i] == '\n' || s[i] == ' ')
				{
					state = 24;
				}
				else 
				{
					return -1;
				}
				break;
			case 24:
				return 6;
			default:
				return -1;
		}
		i++;
	}
	return -1;
}



int main()
{
	char c;
	int cnt = 0;
	string s;
	while(true)
	{	
		c = getchar();
		s.push_back(c);
		cnt++;
		if(c == '\n' || c == ' ')
		{
			break;
		}
	}
	int val = machine(s,cnt);
	switch(val)
	{
		case 1:
			cout<<"Token: BEGIN  CODE : 1\n";
			break;
		case 2:
			cout<<"Token: END  CODE : 2\n";
			break;
		case 3:
			cout<<"Token: IF  CODE : 3\n";
			break;
		case 4:
			cout<<"Token: THEN  CODE : 4\n";
			break;
		case 5:
			cout<<"Token: ELSE CODE : 5\n";
			break;
		case 6:
			cout<<"Token: IDENTIFIER  CODE : 6\n";
			break;
		default:
			cout<<"Not identified Constant\n";
			break;
	}
	return 0;
}