%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yylval;
void yyerror(char *s);
%}

%token NAME NUMBER

%left '-' '+'
%left '*' '/'

%%
statement : NAME '=' expression
	| 		expression	{ printf("=%d\n",$1); }
	;

expression : expression '+' expression { $$  = $1 + $3; }
	|		 expression '-' expression { $$  = $1 - $3; }
	|		 expression '*' expression { $$  = $1 * $3; }
	|		 expression '/' expression { if($3 == 0){yyerror("divided by 0");}$$  = $1 / $3; }
	|		 NUMBER				   { $$ = $1; }
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
