#include"BNFUnit.h"

BNFUnit::BNFUnit() { type = 0; }
BNFUnit::BNFUnit(string s) { name = s; type = 0; }
void BNFUnit::setName(string s) { name = s; }
string BNFUnit::getName() { return name; }
int BNFUnit::getType() { return type; }