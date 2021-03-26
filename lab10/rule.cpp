#include"rule.h"

Rule::Rule(string s) 
{
    name = s;    
}

RuleUnit* Rule::createNewUnit()
{
    RuleUnit* newUnit = new RuleUnit();
    ruleContent.push_back(newUnit);
    return newUnit;
}

string Rule::getRuleString()
{
    string rule = name;
    rule += " -> ";
    for(int c = 0; c < ruleContent[0]->unitContent.size(); c++)
    {
        rule += "<" + ruleContent[0]->unitContent[c]->getName() + ">";
    }
    return rule;
}