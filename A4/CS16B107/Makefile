a.out: lex.yy.o a4.cc
	c++ -std=c++14 lex.yy.o a4.cc
	@echo "Run the program as ./a.out <input.txt"

lex.yy.o: lex.yy.c a4.hh
	cc -c lex.yy.c

lex.yy.c: a4.l
	lex a4.l

a4.hh a4.cc: a4.y
	yacc -d a4.y -o a4.cc

clean:
	@rm lex.yy.c a4.hh a4.cc lex.yy.o a.out
