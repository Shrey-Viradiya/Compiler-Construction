%{
    #include<stdio.h>
    #include<string.h>
    int vow_count=0;
    int conso_count =0;
%}

%%

[\n] return 0;
[\t]+ ;
[aeiou] {vow_count++ ;}
[a-zA-Z] {conso_count++ ;}

%%

int main()
{
    printf("Enter the string of vowels and consonents:");
    yylex();
    printf("\nNumer of Vowels are %d and Consonants are %d",vow_count, conso_count);
    return 0;
}

int yywrap(){
    return 0;
}
int yyerror(){
    return 0;
}