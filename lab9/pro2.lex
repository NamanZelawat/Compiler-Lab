%{
#include "y.tab.h"
%}

%option noyywrap
 
%%
a {strcpy(yylval.c,yytext);return TEXT2;}
b {strcpy(yylval.c,yytext);return TEXT1;}
[ \t] ;
\n return 0;
. return yytext[0];
%% 