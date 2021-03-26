#ifndef ruleH
#define ruleH

#include<bits/stdc++.h>
#include"ruleUnit.h"

using namespace std;

class Rule
{
	public:
        vector<RuleUnit*> ruleContent;
        string name;
        vector<string> firstSet;
		vector<string> followSet;
        
		Rule(string);
		RuleUnit* createNewUnit();
		string getRuleString();
};

#endif