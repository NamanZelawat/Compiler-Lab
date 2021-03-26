#ifndef itemH
#define itemH

#include<bits/stdc++.h>

using namespace std;

class Item
{
    public :
    	int ruleNumber;
        int pointPosition;
        bool isRead;

        Item() 
        { 
        	isRead = false; 
        }
        Item(int rNumber, int pos) 
        { 
        	ruleNumber = rNumber; pointPosition = pos; 
        }
};

#endif