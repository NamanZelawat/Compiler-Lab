#ifndef parsingTableActionH
#define parsingTableActionH

#include<bits/stdc++.h>
#include"rule.h"

using namespace std;

class ParsingTableAction
{
    public :
        /* Type 1 - Shift, Type 2 - Reduce, Type 3 - Accept, Type 4 - Goto */
        int type;
        string shiftTo;
        string goTo;
        Rule* reduceRule;
        
        ParsingTableAction(int t) 
        { 
        	type = t;
        }
        friend bool operator< (ParsingTableAction &cC1, ParsingTableAction &cC2);
};
#endif