%{ 
	#include<stdio.h>
	int yyerror(char *errormsg);
%} 

%%
BEGIN {printf("%s KEYWORD code 1 value -\n",yytext);}
END {printf("%s KEYWORD code 2 value -\n",yytext);}
IF {printf("%s KEYWORD code 3 value -\n",yytext);}
THEN {printf("%s KEYWORD code 4 value -\n",yytext);}
ELSE {printf("%s KEYWORD code 5 value -\n",yytext);}
[a-zA-Z]+[a-zA-Z0-9]* {printf("%s IDENTIFIER code 6\n", yytext);}
[0-9]+ {printf("%s CONSTANT code 7\n", yytext);}
"<" {printf("%s RELATIONAL OPERATOR code 8 value 1\n", yytext);}
"<=" {printf("%s RELATIONAL OPERATOR code 8 value 2\n", yytext);}
"=" {printf("%s RELATIONAL OPERATOR code 8 value 3\n", yytext);}
"<>" {printf("%s RELATIONAL OPERATOR code 8 value 4\n", yytext);}
">" {printf("%s RELATIONAL OPERATOR code 8 value 5\n", yytext);}
">=" {printf("%s RELATIONAL OPERATOR code 8 value 6\n", yytext);}
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
