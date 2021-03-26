#ifndef terminalH
#define terminalH

#include<bits/stdc++.h>
#include"BNFUnit.h"

using namespace std;

class Terminal : public BNFUnit 
{
	public:
		/* Constructor */
		Terminal();
		Terminal(string);
};

#endif