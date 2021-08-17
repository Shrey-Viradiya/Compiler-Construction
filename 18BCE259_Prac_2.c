// To implement a Recursive Descent Parser Algorithm for Grammer

// S --> E + i
// E --> i * E | t

#include <stdio.h>

char l;
int fail = 0;

void match(char next){
    if (l == next)
    {
        l = getchar();
    }
    else
    {
        printf("Error");
        fail = 1;
    }  
}

void E(){
    if (l == 'i')
    {
        match('i');
        match('*');
        E();
    }
    else if (l == 't')
    {
        match('t');
    }    
}

void S(){
    E();
    if (l == '+')
    {
        match('+');
        match('i');
    }
    
}

int main(){
    l = getchar();

    S();

    if (!fail) printf("Success");
}