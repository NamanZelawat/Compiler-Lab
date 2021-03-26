build:
	g++ -c BNFUnit.cpp 
	g++ -c debug.cpp 
	g++ -c grammar.cpp 
	g++ -c item.cpp
	g++ -c link.cpp
	g++ -c nonterminal.cpp
	g++ -c parser.cpp
	g++ -c parsingTableAction.cpp
	g++ -c rule.cpp
	g++ -c ruleUnit.cpp
	g++ -c slrParserGenerator.cpp
	g++ -c state.cpp
	g++ -c terminal.cpp
	g++ -c main.cpp

exec:
	g++ BNFUnit.o debug.o grammar.o item.o link.o nonterminal.o parser.o parsingTableAction.o rule.o ruleUnit.o slrParserGenerator.o state.o terminal.o main.o -o main

run:
	./main

clean:
	rm -rf *.o

all:
	make build
	make exec
	make clean
	make run
	
