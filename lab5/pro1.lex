%{ 
#include<stdio.h>
#include<ctype.h>
int yyerror(char *errormsg);
%} 

%%
[!@#$&*_][0-9a-zA-Z]* {printf("TOKEN --> 1\n");}
[0-9]([!@#$&*_]|[a-zA-Z])* {printf("TOKEN --> 2\n");}
^[A-Za-z]([A-Za-z0-9]|[!@#$&*_])*(?:_[A-Za-z0-9]+)*$ {printf("TOKEN --> 3\n");}
" " {}
\n {}
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

