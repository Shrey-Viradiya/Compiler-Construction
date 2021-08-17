%{
    int n = 0;
%}

%%

"while"|"if"|"else"|"return"|"break"|"case"|"for"|"NULL"|"struct"|"switch"|"continue"|"do"|"default" {n++; printf("\n keywords : %s", yytext);}  
"int"|"float"|"bool" {n++; printf("\n keywords : %s", yytext);}   
[a-zA-Z_][a-zA-Z0-9_]* {n++; printf("\n identifier : %s", yytext);} 
"<="|"=="|"="|"++"|"-"|"*"|"+" {n++; printf("\n operator : %s", yytext);}
[(){}|,;]    {n++; printf("\n separator : %s", yytext);}
[0-9]*"."[0-9]+ {n++; printf("\n float : %s", yytext);}  
[0-9]+ {n++; printf("\n integer : %s", yytext);}
.    ;

%%
int yywrap()
{
    return 1;
}

int main()
{
    extern FILE *yyin, *yyout;

    yyin=fopen("Graph_Color_implementation.c","r");
    yylex();
    printf("\nNo of tokens: %d\n", n);
}