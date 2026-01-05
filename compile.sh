bison -d script.y; flex script.l; gcc script.tab.c lex.yy.c -o game -lfl
