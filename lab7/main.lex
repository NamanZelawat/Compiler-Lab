%{
#include "y.tab.h"
%}

%option noyywrap

%%
[abc]+ {yylval.s = yytext;return STRING;}
[ \t] ;
\n return 0;
. return yytext[0];
%%