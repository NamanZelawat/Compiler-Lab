#ifndef stateH
#define stateH

#include<bits/stdc++.h>
#include"item.h"
#include"link.h"

using namespace std;

class State
{
    public:
    	string name;
        vector<Item*> items;
        vector<Link*> links;
        bool isDone;

        State() 
        { 
        	isDone = false; 
        }
        State(string n) 
        { 
        	isDone = false; name = n; 
        }
};

#endif