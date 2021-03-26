%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int yylex();
int yylval;
void yyerror(char *s);
int power(int a,int b);
%}

%token NAME NUMBER

%left '-' '+'
%left '*' '/'
%left '$'
%nonassoc UMINUS

%%
statement : NAME '=' expression
	| 		expression	{ printf("=%d\n",$1); }
	;

expression:	expression '+' expression { $$ = $1 + $3; }
	|	expression '-' expression { $$ = $1 - $3; }
	|	expression '$' expression { $$ = power($1,$3); }
	|	expression '*' expression { $$ = $1 * $3; }
	|	expression '/' expression
				{	if($3 == 0.0)
						yyerror("divide by zero");
					else
						$$ = $1 / $3;
				}
	|	'-' expression %prec UMINUS	{ $$ = -$2; }
	|	'(' expression ')'	{ $$ = $2; }
	|	NUMBER
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

int power(int a,int b)
{
	int res = 1;
	for(int i = 0;i<b;i++)
	{
		res *= a;
	}
	return res;
}
