lextest: driver.o lex.yy.o errormsg.o util.o string_token.o
	cc -g -o lextest driver.o lex.yy.o errormsg.o util.o string_token.o

driver.o: driver.c tokens.h errormsg.h util.h
	cc -g -c driver.c

errormsg.o: errormsg.c errormsg.h util.h
	cc -g -c errormsg.c

lex.yy.o: lex.yy.c tokens.h errormsg.h util.h
	cc -g -c lex.yy.c

lex.yy.c: tiger.lex
	lex tiger.lex

util.o: util.c util.h
	cc -g -c util.c

string_token.o: string_token.c string_token.h
	cc -g -c string_token.c

clean: 
	rm -f a.out util.o driver.o lex.yy.o lex.yy.c errormsg.o string_token.o
