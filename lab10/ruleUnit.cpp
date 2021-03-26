#include"ruleUnit.h"

RuleUnit::RuleUnit() {}

void RuleUnit::add(BNFUnit* bnf)
{
    unitContent.push_back(bnf);
}