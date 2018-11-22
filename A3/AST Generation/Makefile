a.out: lex.yy.o a2.cc
	c++ -std=c++14 lex.yy.o a2.cc
	@echo "Run the program as ./a.out <input.txt"

lex.yy.o: lex.yy.c a2.hh
	cc -c lex.yy.c

lex.yy.c: a2.l
	lex a2.l

a2.hh a2.cc: a2.y
	yacc -d --debug --verbose a2.y -o a2.cc

clean:
	@rm lex.yy.c a2.hh a2.cc lex.yy.o a.out
