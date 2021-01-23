%{ 
#include<stdio.h>
int yyerror(char *errormsg);
%} 

%%
(begin|end|if|then|else|for|do|while|switch|case|default|break|continue|goto)"\n" {printf("%s TOKEN KEYWORD\n",yytext);}
"/*"(.|" ")*"*/\n" {printf("%s TOKEN COMMENT\n", yytext);}
([_a-zA-Z]+[_a-zA-Z0-9]*)"\n" {printf("%s TOKEN IDENTIFIER\n", yytext);}
[0-9]+"\n" {printf("%s TOKEN DIGIT\n", yytext);}
" " {}
. {yyerror("Unknown char");}
%%
  
int yywrap()								
{
}

int main(void)
{
	yylex();
	return 0;
}

int yyerror(char *errormsg)
{
      fprintf(stderr, "%s\n", errormsg);
      exit(0);
}
