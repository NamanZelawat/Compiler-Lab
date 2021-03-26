#ifndef slrParserGeneratorH
#define slrParserGeneratorH

#include<bits/stdc++.h>
#include"grammar.h"
#include"state.h"
#include"parsingTableAction.h"

using namespace std;

class SLRParserGenerator
{
    private :
        void findFirstSets();
        void findFollowSets();
        void convertGrammerToAugementedVersion();
        void createStates();
        void createParsingTable();
        void printStates();
        void printParsingTable();
    public :
        Grammar* grammar;
        vector<State*> states;
        map<string, map <string, ParsingTableAction*> > parsingTable;

        SLRParserGenerator() {}
        SLRParserGenerator(Grammar* g) { grammar = g; }

        void generate();
};

#endif