run : 
	yacc -d main.y
	lex main.lex
	gcc lex.yy.c y.tab.c -o main -ll -ly