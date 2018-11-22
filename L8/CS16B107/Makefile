a.out: y.tab.c lex.yy.c
	g++ -std=c++14 lex.yy.c y.tab.c
	@echo "Run the program as ./a.out <input.txt"

y.tab.c: l8.y
	yacc -d l8.y

lex.yy.c: l8.l y.tab.h
	lex l8.l

clean:
	@rm lex.yy.c y.tab.h y.tab.c a.out