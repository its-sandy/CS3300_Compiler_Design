a.out: lex.yy.o a3.cc
	c++ -std=c++14 lex.yy.o a3.cc
	@echo "Run the program as ./a.out <input.txt"

lex.yy.o: lex.yy.c a3.hh
	cc -c lex.yy.c

lex.yy.c: a3.l
	lex a3.l

a3.hh a3.cc: a3.y
	yacc -d a3.y -o a3.cc

clean:
	@rm lex.yy.c a3.hh a3.cc lex.yy.o a.out
