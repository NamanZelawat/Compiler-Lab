%{ 
#include<stdio.h>
#include<ctype.h>
int yyerror(char *errormsg);
char* upper(char *s);
%} 

%%
(int)"\n" {printf("TOKEN --> %s",upper(yytext));}
(char)"\n" {printf("TOKEN --> %s",upper(yytext));}
(float)"\n" {printf("TOKEN --> %s",upper(yytext));}
(double)"\n" {printf("TOKEN --> %s",upper(yytext));}
("long int")"\n" {printf("TOKEN --> %s",upper(yytext));}
(\+|-)?(([0-9]+)|([0-9]*)) {printf("TOKEN --> INTEGER\n");}
(\+|-)?(([0-9]+)|([0-9]*\.[0-9]+)|([0-9]*\/[0-9]+)([eE][-+]?[0-9]+)?) {printf("TOKEN --> FLOAT\n");}
=|<>|<|>|<=|>= {printf("TOKEN --> %s\n",yytext);}
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
