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
"GRIDSIZE"  { return GRIDSIZE; }
"HEALTH"    { return HEALTH; }
"INVENTORY" { return INVENTORY; }
"USE"       { return USE; }
"RANDOM"    { return RANDOM; }
"SOUND"     { return SOUND; }
"WAIT"      { return WAIT; }
"TELEPORT"  { return TELEPORT; }
"STATUS"    { return STATUS; }
"ATTACK"    { return ATTACK; }
"MISSION"   { return MISSION; }
"GENERATE"  { return GENERATE; }
"THEME"     { return THEME; }
"COMPLETE"  { return COMPLETE; }
"ADAPT"     { return ADAPT; }
"POPULATE"  { return POPULATE; }
"EXIT"      { return EXIT; }
"UP"|"DOWN"|"LEFT"|"RIGHT" { yylval.str = strdup(yytext); return DIRECTION; }
"OBSTACLE"|"ITEM"|"ENEMY"|"POWERUP"|"WALL"|"DOOR" { yylval.str = strdup(yytext); return OBJECT_TYPE; }

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
