#ifndef ruleUnitH
#define ruleUnitH

#include<bits/stdc++.h>
#include"BNFUnit.h"

using namespace std;

class RuleUnit
{
    public:
        vector<BNFUnit*> unitContent;
        
        /* Methods */
        RuleUnit();
        void add(BNFUnit*);
};

#endif