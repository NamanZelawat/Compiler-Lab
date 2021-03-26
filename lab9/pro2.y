 %{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int yylex();
void yyerror(char *s);
%}

%union {
	char c[40];
}

%token<c> TEXT1
%token<c> TEXT2
%type<c> statement

%%
statement : 'i' TEXT1 't' statement 'e' statement { printf("parsing success\n"); }
	|		'i' TEXT1 't' statement { printf("parsing success\n"); }
	|		TEXT2 { strcpy($$,$1); }
	;

%%

extern FILE *yyin;
int main()
{
	do
	{
		yyparse();
	}
	while(!feof(yyin));
}

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(0);
}