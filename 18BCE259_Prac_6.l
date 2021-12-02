%{
    #include <stdio.h>
    #include "y.tab.h"
    void yyerror(char *);
%}

%%
[0-9]+? {yylval.sym=(char)yytext[0]; return NUMBER;}
[a-zA-Z]+? {yylval.sym=(char)yytext[0]; return LETTER;}
\n {return 0;}
. {return yytext[0];}
%%

void yyerror(char *s) {
   fprintf(stderr, "%s\n", s);
}

int yywrap()
{
 return 1;
}