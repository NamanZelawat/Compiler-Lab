#include"slrParserGenerator.h"

void SLRParserGenerator::generate()
{
    Debug::write("Creating First and Follow Sets...");
    findFirstSets();
    findFollowSets();
    Debug::write("First and follow sets are constructed!");
    Debug::write("Converting grammer to augemented version...");
    convertGrammerToAugementedVersion();
    grammar->createUniqueRules();
    Debug::write("Converting is done!");
    Debug::write("Creating Canonical Closure Sets(States)...");
    createStates();
    Debug::write("Canonical Closure Sets(States) Done!");
    printStates();
    Debug::write("Creating parsing table...");
    createParsingTable();
    Debug::write("Parsing Table is done!");
    printParsingTable();
}


void SLRParserGenerator::findFirstSets()
{
    for(int r = 0; r < grammar->rules.size(); r++) 
    {
        vector<string> firsts = grammar->getFirstOf(grammar->rules[r]->name);
        for(int j = 0; j < firsts.size(); j++)
        {
            vector<string>::iterator result = find( grammar->rules[r]->firstSet.begin(), 
                                                     grammar->rules[r]->firstSet.end(), 
                                                    firsts[j]);
            if (result == grammar->rules[r]->firstSet.end()) 
            {
                grammar->rules[r]->firstSet.push_back(firsts[j]);
            }
        }
    }

    /* First Set Debug */
    Debug::writeTitle("First Sets :");
    for(int r = 0; r < grammar->rules.size(); r++) {
        string unitContent = "{";
        for(int k = 0; k < grammar->rules[r]->firstSet.size(); k++)
        {
            unitContent += grammar->rules[r]->firstSet[k];
            if(k < grammar->rules[r]->firstSet.size() -1 )unitContent += ",";
        }
        unitContent += "}";
        Debug::write("First of " + grammar->rules[r]->name + " : " + unitContent);                
    }
}

void SLRParserGenerator::findFollowSets()
{
    grammar->rules[0]->followSet.push_back("$");

    for(int r = 0; r < grammar->rules.size(); r++) 
    {
        vector<string> follows = grammar->getFollowOf(grammar->rules[r]->name);
        for(int j = 0; j < follows.size(); j++)
        {
            vector<string>::iterator result = find( grammar->rules[r]->followSet.begin(), 
                                                     grammar->rules[r]->followSet.end(), 
                                                    follows[j]);
            if (result == grammar->rules[r]->followSet.end()) 
            {
                grammar->rules[r]->followSet.push_back(follows[j]);
            }
        }
    }
    
    /* Follow Set Debug */
    Debug::writeTitle("Follow Sets");
    for(int r = 0; r < grammar->rules.size(); r++) {
        string unitContent = "{";
        for(int k = 0; k < grammar->rules[r]->followSet.size(); k++)
        {
            unitContent += grammar->rules[r]->followSet[k];
            if(k < grammar->rules[r]->followSet.size() -1 )unitContent += ",";
        }
        unitContent += "}";
    
        Debug::write("Follow of " + grammar->rules[r]->name + " : " + unitContent);                
    }
}

void SLRParserGenerator::convertGrammerToAugementedVersion()
{
    string dumyName = "S'";
    
    Rule* dumyRule = new Rule(dumyName);
    RuleUnit* dumyUnit = dumyRule->createNewUnit();
    
    string rootName = grammar->rules[0]->name;
    BNFUnit* nonTerminal = new NonTerminal(rootName);
    dumyUnit->add(nonTerminal);
    
    vector<Rule*> orderedRule;
    orderedRule.push_back(dumyRule);
    for(int r = 0; r < grammar->rules.size(); r++)
    {
        orderedRule.push_back(grammar->rules[r]);
    }
    
    grammar->rules.clear();
    grammar->rules = orderedRule;
    
    Debug::writeTitle("Converted BNF");
    Debug::write(grammar->getBNF());
}

void SLRParserGenerator::createStates()
{
    int stateNameCounter = 1;
    
    State* initialState = new State("s0");
    initialState->items.push_back(new Item(0,0));
    
    states.push_back(initialState);
    //createDerivations(states.size() - 1);
    

    /* Loops through states */
    for(int i = 0; i < states.size(); i++)
    {   
        /* Creates the Derivations */ 
        vector<string> addedRules;
        for(int y = 0; y < states[i]->items.size(); y++)
        {
            string next = grammar->getNextNonTerminal(states[i]->items[y]->ruleNumber,
                                                    states[i]->items[y]->pointPosition
                                                    );
            if(next != "")
            {
                
                vector<string>::iterator result = find(addedRules.begin(), addedRules.end(), next);
                if (result == addedRules.end()) 
                {
                    addedRules.push_back(next);
                    for(int z = 0; z < grammar->uniqueRules.size(); z++)
                    {
                        if(grammar->uniqueRules[z]->name == next)
                        {
                            states[i]->items.push_back(new Item(z, 0));
                        }                  
                    }
                }
            }                                       
        }
        addedRules.clear();
        /* Derivation Ends */
        
        /* Create new states */
        for(int y = 0; y < states[i]->items.size(); y++)
        {
            string next = grammar->getNextNonTerminal(states[i]->items[y]->ruleNumber,
                                                    states[i]->items[y]->pointPosition
                                                    );
            
            if(next != "")
            {
                int r = states[i]->items[y]->ruleNumber;
                int p = states[i]->items[y]->pointPosition + 1;
                
                bool isNewState = true;
                
                for(int z = 0; z < states[i]->links.size(); z++)
                {
                    if(states[i]->links[z]->labelName == next)
                    {
                        isNewState = false;
                        
                        bool alreadyIn = false;
                        for(int l = 0; l < states[i]->links[z]->targetState->items.size(); l++)
                        {
                            if(states[i]->links[z]->targetState->items[l]->ruleNumber == r
                               && states[i]->links[z]->targetState->items[l]->pointPosition == p)
                            {
                                alreadyIn = true;
                            }
                        }
                        if(!alreadyIn)
                        {
                            states[i]->links[z]->targetState->items.push_back(new Item(r, p));
                        }
                        break;
                    }
                }
                
                if(isNewState) {
                    
                    bool isInPreviousStates = false;
                    
                    for(int s = 0; s < states.size(); s++)
                    {
                        for(int t = 0; t < states[s]->items.size(); t++)
                        {
                            if(states[s]->items[t]->ruleNumber == r
                                && states[s]->items[t]->pointPosition == p
                                && !isInPreviousStates)
                            {
                                isInPreviousStates = true;
                                states[i]->links.push_back(new Link(next, states[s]));
                            }    
                        }
                    }
                     
                    if(!isInPreviousStates)
                    {
                        stringstream ss;
                        ss << stateNameCounter;
                        stateNameCounter++;
                        State* tempState = new State("s" + ss.str());    
                        tempState->items.push_back(new Item(r, p));
                        
                        states[i]->links.push_back(new Link(next, tempState));   
                        states.push_back(tempState);
                    }
                    
                }
            }
        }
        /* Create new states end */
    }
}

void SLRParserGenerator::createParsingTable()
{
    
    vector<string> terminals, nonterminals;
    
    /* Populating NonTerminals */
    for(int i = 0; i < grammar->rules.size(); i++)
    {
        nonterminals.push_back(grammar->rules[i]->name);
    }
    
    /* Populating Terminals */
    terminals.push_back("$");
    for(int i = 0; i < grammar->uniqueRules.size() ; i++)
    {
        vector<BNFUnit*> content = grammar->uniqueRules[i]->ruleContent[0]->unitContent;
        for(int y = 0; y < content.size(); y++)
        {
            if(content[y]->getType() == 2)
            {
                vector<string>::iterator result = find(terminals.begin(), terminals.end(), content[y]->getName());
                if (result == terminals.end()) 
                {
                    terminals.push_back(content[y]->getName());
                }
            }
        }
    }
    
    /* Constracting Parsing Table */
    for(int stateNo = 0; stateNo < states.size(); stateNo++)
    {
        map<string, ParsingTableAction*> x;
        
        /* CASE (a) */
        for(int links = 0; links < states[stateNo]->links.size(); links++)
        {
            vector<string>::iterator result = find(terminals.begin(), terminals.end(), states[stateNo]->links[links]->labelName);
            if (result != terminals.end()) 
            {
                ParsingTableAction* action = new ParsingTableAction(1);
                action->shiftTo = states[stateNo]->links[links]->targetState->name;
                x[states[stateNo]->links[links]->labelName] = action;
            }
        } 
        
        /* CASE (b) */
        for(int item = 0; item < states[stateNo]->items.size(); item++)
        {
            int ruleNumber = states[stateNo]->items[item]->ruleNumber;
            int point = states[stateNo]->items[item]->pointPosition;
                    
            vector<BNFUnit*> content = grammar->uniqueRules[ruleNumber]->ruleContent[0]->unitContent;
            
            if(point == content.size())
            {
                for(int rule = 0; rule < grammar->rules.size(); rule++)
                {
                    if(grammar->rules[rule]->name == grammar->uniqueRules[ruleNumber]->name)
                    {
                        for(int flw = 0; flw < grammar->rules[rule]->followSet.size(); flw++)
                        {
                            ParsingTableAction* action = new ParsingTableAction(2);
                            action->reduceRule = grammar->uniqueRules[ruleNumber];
                            x[grammar->rules[rule]->followSet[flw]] = action;
                        }
                    }
                }
            }
        }
        
        /* CASE (c) */
        bool acc = false;
        for(int item = 0; item < states[stateNo]->items.size(); item++)
        {
            int ruleNumber = states[stateNo]->items[item]->ruleNumber;
            int point = states[stateNo]->items[item]->pointPosition;
            if(ruleNumber == 0 && point == 1)
            {
                acc = true;
            }
        }
        if(acc)
        {
            ParsingTableAction* action = new ParsingTableAction(3);
            x["$"] = action;
        }
        
        /* Constructing GOTO's */
        for(int nt = 0; nt < nonterminals.size(); nt++)
        {
            for(int link = 0; link < states[stateNo]->links.size(); link++)
            {
                if(states[stateNo]->links[link]->labelName == nonterminals[nt])
                {
                    ParsingTableAction* action = new ParsingTableAction(4);
                    action->goTo = states[stateNo]->links[link]->targetState->name;
                    x[nonterminals[nt]] = action;
                }
            }   
        }
        
        parsingTable[states[stateNo]->name] = x;
    }
    
}
void SLRParserGenerator::printStates()
{
    Debug::writeTitle("States");
    for(int i = 0; i < states.size(); i++)
    {
        Debug::write("\n----------------------------------------");
        Debug::write("State Name : " + states[i]->name);
        for(int z = 0; z < states[i]->links.size(); z++)
        {
            Debug::write("( goes to " + states[i]->links[z]->targetState->name + " when reads : " + states[i]->links[z]->labelName + ")");
        }
        Debug::write("----------------------------------------");
        
        for(int y = 0; y < states[i]->items.size(); y++)
        {
            Item* temp = states[i]->items[y];
            string content = grammar->getRuleContent(temp->ruleNumber, temp->pointPosition);
            Debug::write(content);    
        }
        
    }
}

void SLRParserGenerator::printParsingTable()
{
    Debug::writeTitle("Parsing Table");
    map <string, map<string, ParsingTableAction*> >::iterator curr;
    map <string, ParsingTableAction*>::iterator curr2;
    
    for( curr = parsingTable.begin(); curr != parsingTable.end();  ++curr)
    {
        Debug::write(curr->first + " -> ");
        for( curr2 = curr->second.begin(); curr2 != curr->second.end(); ++curr2 )
        {
            if(curr2->second->type == 1)
                Debug::write("\t(" + curr2->first + ", shift to " + curr2->second->shiftTo + ")");
                
            if(curr2->second->type == 2)
            {
                Rule* r = curr2->second->reduceRule;
                Debug::write("\t(" + curr2->first + ", reduce " + r->getRuleString() + ")");
            }
            if(curr2->second->type == 3)
                Debug::write("\t(" + curr2->first + ", accept)");
                
            if(curr2->second->type == 4)
                Debug::write("\t(" + curr2->first + ", goto " + curr2->second->goTo + ")");
        }
    }
    
    
}