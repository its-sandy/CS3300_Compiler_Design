a.out: lex.yy.o l10.cc
	c++ -std=c++14 lex.yy.o l10.cc
	@echo "Run the program as ./a.out <input.txt"

lex.yy.o: lex.yy.c l10.hh
	cc -c lex.yy.c

lex.yy.c: l10.l
	lex l10.l

l10.hh l10.cc: l10.y
	yacc -d l10.y -o l10.cc

clean:
	@rm lex.yy.c l10.hh l10.cc lex.yy.o a.out
