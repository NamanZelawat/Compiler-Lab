%{
#include "y.tab.h"
int yyerror(char *errormsg);
int yyparse();
%}
  
%%
("hi"|"oi"|"hola"|"namastey")       { return HI;  };
.                 { yyerror("Unknow char");  }

%%

int main(void)
{
     yyparse();
     return 0;
}

int yywrap(void)
{
     return 0;
}

int yyerror(char *errormsg)
{
      fprintf(stderr, "%s\n", errormsg);
      exit(1);
}