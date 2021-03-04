%{
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int yylex();
void yyerror(char *s);
int check;
int st,end;
%}

%union{
	char *s;
}
 
%token <s> STRING 
%type <s> expression 

%%
statement : expression {
	check = 1;
	st = 0;
	end = strlen($1)-1;
	if((end+1)%2 == 0)
	{
		printf("Failed\n");
		return 0;
	}
	while(st < end)
	{
		if($1[st] != $1[end] || ($1[st] != 'a' && $1[st] != 'b') || ($1[end] != 'a' && $1[end] != 'b') )
		{
			check = 0;
			break;
		}
		st++;
		end--;
	}
	if(st != end || $1[st] != 'c')
	{
		check = 0;
	}
	if(check)
	{
		printf("Success\nBye\n");
	}
	else
	{
		printf("Failed\n");
		return 0;
	}
}

expression : STRING {$$ = $1;};
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
