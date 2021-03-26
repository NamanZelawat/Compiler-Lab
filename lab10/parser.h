#ifndef parserH
#define parserH

#include<bits/stdc++.h>
#include"slrParserGenerator.h"

using namespace std;

class Parser
{
    private :
        static string inputStream;
        SLRParserGenerator* parserGenerator;
        int streamPointer;
        string getNextStream();
        stack<string> stateStack;

    public :
        Parser() { streamPointer = 0; }
        Parser(SLRParserGenerator* gen) { parserGenerator = gen; streamPointer = 0; }

        void loadInputFromFile(string);
        void parse();
};

#endif