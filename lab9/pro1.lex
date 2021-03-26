%{
#include<math.h>
#include "y.tab.h"
extern int yylval;
%}

%option noyywrap
 
%%
[a-zA-z][0-9A-Za-z]* {yylval = atoi(yytext);return NAME;}
[0-9]+ {yylval = atoi(yytext);return NUMBER;}
[ \t] ;
\n return 0;
. return yytext[0];
%% 