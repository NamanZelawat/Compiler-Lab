%{ 
#include<stdio.h>
#include<ctype.h>
int yyerror(char *errormsg);
%} 

%%
((a+b)*(c+d)*)+(ab*c*d) {printf("TOKEN 1 --> %s\n",yytext);}
((01*2)+(0*2)+(1))+ {printf("TOKEN 3 --> %s\n",yytext);}
((0+1)*+(0*1*)) {printf("TOKEN 2 --> %s\n",yytext);}
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
