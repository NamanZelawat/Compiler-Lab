#include"parsingTableAction.h"

bool operator< (ParsingTableAction &cC1, ParsingTableAction &cC2) 
{
    return cC1.type < cC2.type;
}
