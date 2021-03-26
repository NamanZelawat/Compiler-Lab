#ifndef linkH
#define linkH

#include<bits/stdc++.h>

class State;

using namespace std;

class Link
{
    public :
        string labelName;
        State* targetState;

        Link() {}
        Link(string l, State* s) 
        { 
        	labelName = l; targetState = s; 
        }
};

#endif