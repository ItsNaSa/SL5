%{
    //definition section
    #include<stdio.h>
    #include"y.tab.h"
    extern int yylval;
%}

/*starting rule section*/
%%
[0-9]+ {
            yylval = atoi(yytext);
            return NUMBER;
        }
[\t] ;

[\n] return 0;

. return yytext[0];

%%

//defined own yywrap as to reduce error
// If someone calls the compiler with multiple source files, we store them in a list or array, 
// and then yywrap() is called at the end of each file to give you a chance to continue with a new file.
int yywrap(){
    return 1;
}