#include"parser.h"

string Parser::inputStream = "";

void Parser::loadInputFromFile(string fileName)
{
    ifstream reader;
    reader.open(fileName.c_str());
    string content = "";
    
    while(!reader.eof()) 
    {
        string line;
        getline(reader,line);
        content += line;
    }
    
    reader.close();
    
    Parser::inputStream = content;
}

string Parser::getNextStream()
{
   
    if(streamPointer >= Parser::inputStream.length()) return "$";
    char temp = Parser::inputStream[streamPointer];
    streamPointer++;
    stringstream ss;
    ss << temp;
    return ss.str();
}

void Parser::parse()
{
    Debug::writeTitle("Parsing Results");
    
    /* Initilazing the Stack */
    stateStack.push(parserGenerator->states[0]->name);

    string readedStream = "";   
    string currentStream = getNextStream();
    
    while(true)
    {
        map<string, ParsingTableAction*>::iterator result = parserGenerator->parsingTable[stateStack.top()].find(currentStream);
        if (result == parserGenerator->parsingTable[stateStack.top()].end()) 
        {
            /* Error Recovery Mode */
            readedStream += currentStream;
            int remaining = 8 - readedStream.length();
            for(int i = 0; i < remaining; i++)
            {
                readedStream += getNextStream();
            }
            
            while(!stateStack.empty()) stateStack.pop();
            stateStack.push(parserGenerator->states[0]->name);
            
            currentStream = getNextStream();
            Debug::write(readedStream + "(Makamsiz)");
            if(currentStream == "$") break;
            else readedStream = "";
            continue;
        }
         
        ParsingTableAction* action = parserGenerator->parsingTable[stateStack.top()][currentStream];
        
        if(action->type == 1) // Shifting Action
        {
            readedStream += currentStream;
            currentStream = getNextStream();
            stateStack.push(action->shiftTo);
            
        }else if(action->type == 2) // Reduce Action
        {
            Rule* reduceRule = action->reduceRule;
            int popingCount = reduceRule->ruleContent[0]->unitContent.size();
            
            for(int p = 0; p < popingCount; p++)
            {
                stateStack.pop();
            }
            
            
            ParsingTableAction* action = parserGenerator->parsingTable[stateStack.top()][reduceRule->name];
            stateStack.push(action->goTo);
            
            Debug::write(readedStream + reduceRule->getRuleString());
            
            if(reduceRule->name == "Huseyni" || 
                reduceRule->name == "Neva" ||
                reduceRule->name == "Muhayyer" ||
                reduceRule->name == "Tahir" ||
                reduceRule->name == "Ussak")
            {
                Debug::write(readedStream + "(" + reduceRule->name + ")");
                readedStream = "";
            }
        }else if(action->type == 3) // Accept Action
        {
            Debug::write("Accepted");
            break;
        }else
        {
           Debug::write("Not Accepted");
           break; 
        }
    }
}