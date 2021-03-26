#ifndef BNFUnitH
#define BNFUnitH

#include<bits/stdc++.h>

using namespace std;

class BNFUnit
{
    protected:
        string name;
        int type;
	public:
		/* Constructor */
		BNFUnit();
		BNFUnit(string);
		
		void setName(string);
		string getName();
		int getType();
};

#endif