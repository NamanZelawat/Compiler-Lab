%{ 
#include<stdio.h>
int yyerror(char *errormsg);
%} 

%%
[!@#$&*_]+[a-zA-Z0-9]* {printf("%s TOKEN -- 1\n", yytext);}
[0-9][!@#$_&a-zA-Z]+ {printf("%s is a Token2\n",yytext);}
[a-zA-Z]|([a-zA-z]+[!@#$&_0-9a-zA-Z]*[a-zA-Z]+)	 {printf("%s is a Token3\n",yytext);}
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
