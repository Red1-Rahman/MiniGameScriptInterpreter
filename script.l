/* Lexer: script.l
	 Purpose: Hand-written lexical scanner for the MiniGameScript language.
	 I wrote this lexer to produce tokens consumed by the parser in script.y.
	 Notes:
	 - This file is a source artifact (not generated). The compiled lexer
		 `lex.yy.c` is produced at build-time from this file.
	 - Keep token names in sync with script.tab.h / script.y.
	 - Rules should avoid side effects; values are strdup'd into yylval.
*/
%{
#include "script.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

/* Definitions: character classes and token macros */
DIGIT       [0-9]
ID          [a-zA-Z_][a-zA-Z0-9_]*
STRING      \"[^\"]*\"
OP          "=="|"!="|">="|"<="|">"|"<"
ARITHOP     "+"|"-"|"*"|"/"|"%"

/* Rules: keyword/token recognition. Exact-match keywords return token enums. */
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
"RULE"      { return RULE; }
"COLLIDE"   { return COLLIDE; }
"TRANSFORM" { return TRANSFORM; }
"DIFFICULTY" { return DIFFICULTY; }
"AISTEP"    { return AISTEP; }
"SPAWN"     { return SPAWN; }
"BLOCK"     { return BLOCK; }
"DAMAGE"    { return DAMAGE; }
"HEAL"      { return HEAL; }
"SCORE"     { return SCORETOK; }
"DELETE"    { return DELETETOK; }
"EXIT"      { return EXIT; }
"UP"|"DOWN"|"LEFT"|"RIGHT" { yylval.str = strdup(yytext); return DIRECTION; }
"OBSTACLE"|"ITEM"|"ENEMY"|"POWERUP"|"WALL"|"DOOR" { yylval.str = strdup(yytext); return OBJECT_TYPE; }

/* Generic token rules: identifiers, numbers, strings, operators */
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
