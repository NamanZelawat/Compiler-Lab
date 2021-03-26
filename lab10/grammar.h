#ifndef grammarH
#define grammarH

#include<bits/stdc++.h>
#include"rule.h"
#include"debug.h"
#include"nonterminal.h"
#include"terminal.h"

using namespace std;

class Grammar
{       
	public :
        vector<Rule*> rules;
        vector<Rule*> uniqueRules;

        Grammar();
        void loadFromFile(string);
        
        /*Helper methods*/
        string getBNF();
        vector<string> getFirstOf(string);
        vector<string> getFollowOf(string);
        void createUniqueRules();
        int getUnitCount(int);
        string getNextNonTerminal(int, int);
        string getRuleContent(int, int pointer = -1);
};

#endif