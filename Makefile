# dlf

SRC= dlf.c lexical.c grammar.c main.c cfunction.c
OBJ+= $(patsubst %.c,%.o,${SRC})

dlf: ${OBJ}
	$(CC) -o dlf $^

${OBJ}: %.o: %.c
	$(CC) -c -g -O0 -o $@ $<

${SRC}:
	flex -B8 -o lexical.c --header-file=lexical.h lexical.l
	bison -l -t -v -o grammar.c --defines=grammar.h grammar.y

.PHONY : clean

clean:
	rm -rf *.o dlf lexical.c grammar.c lexical.h grammar.h
