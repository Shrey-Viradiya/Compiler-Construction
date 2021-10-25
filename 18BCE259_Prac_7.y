%token IF RELOP S NUMBER ID WHILE
%{
#include <stdio.h>
#include <stdlib.h>
int ifcount=0;
int whilecount=0;
%}

%%
start: stmt {printf("No of If Statements %d\n", ifcount);printf("No of While Statements %d\n", whilecount);exit(0);}
;
stmt: if_stmt
| whl 
| S
;
if_stmt: IF '(' cond ')''{' stmt '}' {ifcount++;}
;
whl: WHILE '(' cond ')''{' stmt '}' {whilecount++;}
;
cond: x RELOP x
;
x: ID
| NUMBER
;
%%
int yyerror(char *msg)
{
printf("Invalid Expression\n");
exit(0);
}
int main ()
{
printf("Enter the statement: ");
yyparse();
}