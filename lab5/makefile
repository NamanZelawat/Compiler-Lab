run1:
	lex pro1.lex
	gcc lex.yy.c
	./a.out

run2:
	yacc -d main.y
	lex main.lex
	gcc lex.yy.c y.tab.c -o main -ll -ly
	./main
