all:
	bison -d script.y
	flex script.l
	gcc script.tab.c lex.yy.c -o game -lfl

clean:
	rm -f game script.tab.c script.tab.h lex.yy.c
