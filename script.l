%{
#include "script.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

DIGIT       [0-9]
ID          [a-zA-Z_][a-zA-Z0-9_]*
STRING      \"[^\"]*\"
OP          "=="|"!="|">="|"<="|">"|"<"
ARITHOP     "+"|"-"|"*"|"/"|"%"

%%

"MOVE"      { return MOVE; }
"SAY"       { return SAY; }
"SET"       { return SET; }
"ADD"       { return ADD; }
"SUBTRACT"  { return SUBTRACT; }
"IF"        { return IF; }
"ENDIF"     { return ENDIF; }
"REPEAT"    { return REPEAT; }
"ENDREPEAT" { return ENDREPEAT; }
"PLACE"     { return PLACE; }
"EXIT"      { return EXIT; }
"UP"|"DOWN"|"LEFT"|"RIGHT" { yylval.str = strdup(yytext); return DIRECTION; }
"OBSTACLE"|"ITEM" { yylval.str = strdup(yytext); return OBJECT_TYPE; }

{ID}        { yylval.str = strdup(yytext); return IDENTIFIER; }
{DIGIT}+    { yylval.num = atoi(yytext); return NUMBER; }
{STRING}    { yylval.str = strdup(yytext); return STRING; }
{OP}        { yylval.str = strdup(yytext); return OPERATOR; }
{ARITHOP}   { yylval.str = strdup(yytext); return ARITHOP; }

[ \t\n]+    { /* skip whitespace */ }
"("         { return '('; }
")"         { return ')'; }
.           { return yytext[0]; }

%%
