#include<bits/stdc++.h>

using namespace std;

class Link;
class Item;
class State;
class Rule;


class Item
{
    public :
        Item() { isRead = false; }
        Item(int rNumber, int pos) { ruleNumber = rNumber; pointPosition = pos; }
        int ruleNumber;
        int pointPosition;
        bool isRead;
};


class State
{
    public: 
        State() { isDone = false; }
        State(string n) { isDone = false; name = n; }
        string name;
        vector<Item*> items;
        vector<Link*> links;
        bool isDone;
};


class Link
{
    public :
        Link() {}
        Link(string l, State* s) { labelName = l; targetState = s; }
        string labelName;
        State* targetState;
};


class ParsingTableAction
{
    public :
        /* Type 1 - Shift, Type 2 - Reduce, Type 3 - Accept, Type 4 - Goto */
        ParsingTableAction(int t) { type = t;}
        int type;
        string shiftTo;
        string goTo;
        Rule* reduceRule;
        
        friend bool operator< (ParsingTableAction &cC1, ParsingTableAction &cC2);
};

bool operator< (ParsingTableAction &cC1, ParsingTableAction &cC2) 
{
    return cC1.type < cC2.type;
}


class BNFUnit
{
    protected:
        string name;
        int type;
	public:
		BNFUnit();
		BNFUnit(string);
		
		void setName(string);
		string getName();
		int getType();
};


class NonTerminal : public BNFUnit
{
	public:
		/* Constructor */
		NonTerminal();
		NonTerminal(string);
		
};


class Terminal : public BNFUnit 
{
	public:
		/* Constructor */
		Terminal();
		Terminal(string);
};


class RuleUnit
{
    public:
        vector<BNFUnit*> unitContent;
        
        /* Methods */
        RuleUnit();
        void add(BNFUnit*);
};


class Rule
{
	public:
        vector<RuleUnit*> ruleContent;
        string name;
        
		Rule(string);
		RuleUnit* createNewUnit();
		string getRuleString();
		
		vector<string> firstSet;
		vector<string> followSet;
};


class Grammar
{       
	public :
        Grammar();
        void loadFromFile(string);
        vector<Rule*> rules;
        vector<Rule*> uniqueRules;
        
        string getBNF();
        vector<string> getFirstOf(string);
        vector<string> getFollowOf(string);
        void createUniqueRules();
        int getUnitCount(int);
        string getNextNonTerminal(int, int);
        string getRuleContent(int, int pointer = -1);
};


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
        SLRParserGenerator() {}
        SLRParserGenerator(Grammar* g) { grammar = g; }
        
        Grammar* grammar;
        void generate();
        vector<State*> states;
        map<string, map <string, ParsingTableAction*> > parsingTable;
};


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
string Parser::inputStream = "";


class Debug
{
    private :
        static string debugFile;
        static bool session;
    public :
        Debug() {}
        static void write(string);
        static void writeTitle(string title);
};
bool Debug::session = false;
string Debug::debugFile = "debug.txt";
