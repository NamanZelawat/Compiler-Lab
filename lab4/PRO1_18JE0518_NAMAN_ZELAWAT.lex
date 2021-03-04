%{ 
#include<stdio.h>
#include<ctype.h>
int yyerror(char *errormsg);
char* upper(char *s);
%} 

%%
(int|char|void|if|else|while|return)"\n" {printf("TOKEN --> %s",upper(yytext));}
(\+|-)?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {printf("TOKEN --> REAL\n");}
"->" {printf("TOKEN --> PTR_OP\n");}
"&&" {printf("TOKEN --> AND_OP\n");}
"||" {printf("TOKEN --> OR_OP\n");}
"." {printf("TOKEN --> DOT_OP\n");}
[\+\-*/] {printf("TOKEN --> %s\n",yytext);}
[;\{\}\,\=\(\)\&~\[\]] {printf("TOKEN --> %s\n",yytext);}
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

char* upper(char *s)
{
	for (int i = 0; s[i]!='\0'; i++) {
      if(s[i] >= 'a' && s[i] <= 'z') {
         s[i] = s[i] -32;
      }
   }
   return s;
}
