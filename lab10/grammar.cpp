#include"grammar.h"

Grammar::Grammar()
{
    Debug::write("Creating grammar...");
}

void Grammar::loadFromFile(string fileName)
{
    ifstream reader;
    reader.open(fileName.c_str());
    string line;
    
    Debug::write("Reading from " + fileName + "...");
    while(!reader.eof()) 
    {
        getline(reader,line);
        
        if(line[0] == '#') { continue; }
        
        Rule* rule;
        RuleUnit* ruleUnit;
        
        bool readingNonTerminal = false;
        bool readingTerminal = false;
        bool switchNewUnit = false;
        string nameHolder = "";
        
        for(int i = 0; i < line.length(); i++)
        {
            if( i < line.length() - 1 && !readingTerminal && line[i+1] == ':')
            {
                rule = new Rule(nameHolder); 
                rules.push_back(rule);
                ruleUnit = rule->createNewUnit();
                readingNonTerminal = false;
                readingTerminal = false;
                switchNewUnit = false;
                nameHolder = "";
                continue;
            }
            
            if(switchNewUnit)
            {
                ruleUnit = rule->createNewUnit();
                switchNewUnit = false;
            }
            
            if(readingNonTerminal)
            {
                if(line[i] == '>')
                {
                    readingNonTerminal = false;
                    readingTerminal = false;
                    Debug::write("\tFound a NonTerminal \"" + nameHolder + "\"" );
                               
                    BNFUnit* nonTerminal = new NonTerminal(nameHolder);
                    ruleUnit->add(nonTerminal);
                    nameHolder = "";
                    continue;
                }else 
                {
                    nameHolder += line.at(i);
                }
            }
            
            if(readingTerminal)
            {
                if(line[i] == '"')
                {
                    readingNonTerminal = false;
                    readingTerminal = false;
                    Debug::write("\tFound a Terminal \"" + nameHolder + "\"" );
                    
                    BNFUnit* terminal = new Terminal(nameHolder);
                    ruleUnit->add(terminal);
                    nameHolder = "";
                    continue;
                }else 
                {
                    nameHolder += line.at(i);
                }
            }
            
            if(line[i] == '<') 
            {
                readingNonTerminal = true;
                readingTerminal = false;
            }
            if(line[i] == '"')
            {
                readingNonTerminal = false;
                readingTerminal = true;
            }
            if(line[i] == '|')
            {
                readingNonTerminal = false;
                readingTerminal = false;
                switchNewUnit = true;
            }
        }
    }
    reader.close();
    createUniqueRules();
    Debug::write("Reading is done!");
    Debug::writeTitle("Constructed BNF");
    Debug::write(getBNF());
}

void Grammar::createUniqueRules()
{
    uniqueRules.clear();
    
    for(int i = 0; i < rules.size(); i++)
    {
        for(int y = 0; y < rules[i]->ruleContent.size(); y++)
        {    
            Rule* dumyRule = new Rule(rules[i]->name);
            RuleUnit* dumyUnit = dumyRule->createNewUnit();
            
            for(int z = 0; z < rules[i]->ruleContent[y]->unitContent.size(); z++)
            {
                string name = rules[i]->ruleContent[y]->unitContent[z]->getName();
                
                if(rules[i]->ruleContent[y]->unitContent[z]->getType() == 1)
                {
                    BNFUnit* nonTerminal = new NonTerminal(name);
                    dumyUnit->add(nonTerminal);
                    
                }else {
                    BNFUnit* terminal = new Terminal(name);
                    dumyUnit->add(terminal);
                }
            }            
            
            uniqueRules.push_back(dumyRule);
        }
    }
}

string Grammar::getBNF()
{
    string bnf = "";
    
    for(int i = 0; i < rules.size(); i++)
    {
        bnf +=  rules[i]->name;
        bnf += " -> "; 
        
        for(int y = 0; y < rules[i]->ruleContent.size(); y++)
        {
            for(int z = 0; z < rules[i]->ruleContent[y]->unitContent.size(); z++)
            {
                string a= rules[i]->ruleContent[y]->unitContent[z]->getName();
                
                if(rules[i]->ruleContent[y]->unitContent[z]->getType() == 2)
                {
                    transform(a.begin(), a.end(), a.begin(), ::tolower);
                }
                
                bnf += a;
                
                if( z < rules[i]->ruleContent[y]->unitContent.size() - 1) 
                {
                    bnf += " ";
                }
            }
            
            if( y < rules[i]->ruleContent.size() - 1)
            {
                bnf += " | "; 
            }
        }
        bnf += "\n";
    }
    
    return bnf;
}



vector<string> Grammar::getFirstOf(string ruleName)
{
    vector<string> result;
    bool isAcceptEmpty = false;
    bool secondTour = false;
    
    for(int i = 0; i < uniqueRules.size(); i++)
    {
        if(uniqueRules[i]->name == ruleName)
        {
            vector<BNFUnit*> content = uniqueRules[i]->ruleContent[0]->unitContent;
            
            if(content[0]->getType() == 1 && content[0]->getName() == ruleName)
            {
                if(secondTour)
                {
                    int p = 1;
                    while(true)
                    {
                        if(p < content.size())
                        {
                            if(content[p]->getType() == 1)
                            {
                                vector<string> temp = getFirstOf(content[p]->getName());
                                result.insert( result.end(), temp.begin(), temp.end() );
                                
                                // Must be test
                                vector<string>::iterator result2 = find(temp.begin(), temp.end(), "_");
                                if (result2 == temp.end()) 
                                {
                                    break;
                                }
                            }else if(content[p]->getType() == 2)
                            {
                                result.push_back(content[p]->getName());      
                                break;
                            } 
                            
                            p++;
                        }else{
                            break;
                        }   
                    }
                    // end of accepty empty situation
                    continue;
                }else
                {
                    continue;
                }
            }
            if(content[0]->getType() == 1)
            {
                vector<string> temp = getFirstOf(content[0]->getName());
                
                
                vector<string>::iterator finder = find(temp.begin(), temp.end(), "_");
                if (finder != temp.end()) 
                {
                    temp.erase(finder);
                    int p = 1;
                    
                    while(true)
                    {
                        if(p < content.size())
                        {
                            if(content[p]->getType() == 1)
                            {
                                vector<string> temp2 = getFirstOf(content[p]->getName());
                                result.insert( result.end(), temp2.begin(), temp2.end() );
                                
                                finder = find(temp2.begin(), temp2.end(), "_");
                                if (finder == temp2.end()) 
                                {
                                    break;
                                }
                            }else if(content[p]->getType() == 2)
                            {
                                result.push_back(content[p]->getName());      
                                break;
                            } 
                            
                            p++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                result.insert( result.end(), temp.begin(), temp.end() );
                
            }else if(content[0]->getType() == 2)
            {
                result.push_back(content[0]->getName());
                if(content[0]->getName() == "_" && !secondTour)
                {
                    isAcceptEmpty = true;
                } 
            }
            
            if(isAcceptEmpty)
            {
                i = -1;
                result.clear();
                isAcceptEmpty = false;
                secondTour = true;
            }
        }
    }
    
    return result;
}

vector<string> Grammar::getFollowOf(string ruleName)
{
    vector<string> result;
    
    for(int i = 0; i < uniqueRules.size(); i++)
    {
        vector<BNFUnit*> content = uniqueRules[i]->ruleContent[0]->unitContent;
        
        for(int y = 0; y < content.size(); y++)
        {
            if(content[y]->getName() == ruleName)
            {
                if(y == content.size() - 1)
                {
                    // Follow(y) includes Follow(uniqueRules[i]->name)
                    if(uniqueRules[i]->name != ruleName)
                    {
                        for(int k = 0; k < rules.size(); k++)
                        {
                            if(rules[k]->name == uniqueRules[i]->name){
                                result.insert( result.end(), rules[k]->followSet.begin(), rules[k]->followSet.end() );
                                break;
                            }
                        }
                    }
                    break;
                }
                
                for(int z = y+1; z < content.size(); z++)
                {
                    if(content[z]->getName() == ruleName)
                    {
                        y = z - 1;                
                        break;
                    }else {
                        if(content[z]->getType() == 1)
                        {
                            vector<string> temp = getFirstOf(content[z]->getName());
                            
                            vector<string>::iterator finder = find(temp.begin(), temp.end(), "_");
                            if (finder != temp.end()) 
                            {
                                temp.erase(finder);
                                result.insert( result.end(), temp.begin(), temp.end() );
                                if(z == content.size() - 1)
                                {
                                    for(int k = 0; k < rules.size(); k++)
                                    {
                                        if(rules[k]->name == uniqueRules[i]->name){
                                            result.insert( result.end(), rules[k]->followSet.begin(), rules[k]->followSet.end() );
                                        }
                                    }
                                }
                            }else {
                                result.insert( result.end(), temp.begin(), temp.end() );
                            }
                            
                            if(z == content.size() - 1) {
                                y = z; break;
                            }
                            
                        }else if(content[z]->getType() == 2) {
                            result.push_back(content[z]->getName());
                            y = z;
                            break;
                        }
                    }
                }     
            }
        }
        
    }
    
    return result;
}

/* Implementation of Helpers */
int Grammar::getUnitCount(int ruleNumber)
{
    return uniqueRules[ruleNumber]->ruleContent[0]->unitContent.size();
}

string Grammar::getNextNonTerminal(int ruleNumber, int position)
{
    string name;
    if(position < uniqueRules[ruleNumber]->ruleContent[0]->unitContent.size())
    {
        return uniqueRules[ruleNumber]->ruleContent[0]->unitContent[position]->getName();
    }else{
        return "";
    }
   
    return "";
}

string Grammar::getRuleContent(int ruleNumber, int pointer)
{
    string rule = uniqueRules[ruleNumber]->name + " --> ";
    
    bool specialCase = false;
    if(uniqueRules[ruleNumber]->ruleContent[0]->unitContent.size() == pointer)
    {
        specialCase = true;
    }
    for(int i = 0; i < uniqueRules[ruleNumber]->ruleContent[0]->unitContent.size(); i++)
    {
        if(pointer != -1 && !specialCase && i==pointer)
        {
            rule += ".";
        }
        rule += "<" + uniqueRules[ruleNumber]->ruleContent[0]->unitContent[i]->getName() + ">";
        
        if(specialCase && i+1 == uniqueRules[ruleNumber]->ruleContent[0]->unitContent.size())
        {
            rule += ".";
        }
    }
    
    return rule;
}