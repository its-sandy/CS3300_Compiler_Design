a.out: lex.yy.o l3.cc
	c++ -std=c++14 lex.yy.o l3.cc
	@echo "Run the program as ./a.out <input.txt"

lex.yy.o: lex.yy.c l3.hh
	cc -c lex.yy.c

lex.yy.c: l3.l
	lex l3.l

l3.hh l3.cc: l3.y
	yacc -d l3.y -o l3.cc

clean:
	@rm lex.yy.c l3.hh l3.cc lex.yy.o a.out

