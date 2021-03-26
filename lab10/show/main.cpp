#include<bits/stdc++.h>
#include "parser.cpp"

using namespace std;

int main()
{     
    Grammar* g = new Grammar();
    g->loadFromFile("grammar.txt");
    
    SLRParserGenerator* parserGenerator = new SLRParserGenerator(g);
    parserGenerator->generate();
    
    Parser* parser = new Parser(parserGenerator); 
    parser->loadInputFromFile("input.txt");
    parser->parse();   

    return 0;
}




