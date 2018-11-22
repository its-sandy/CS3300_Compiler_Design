a.out: y.tab.c lex.yy.c
	g++ -O3 -std=c++14 lex.yy.c y.tab.c
	@echo "Run the program as ./a.out <input.txt"

y.tab.c: l5.y
	yacc -d l5.y

lex.yy.c: l5.l y.tab.h
	lex l5.l

clean:
	@rm lex.yy.c y.tab.h y.tab.c a.out
