.PHONY: clean
GCC_OPTIONS = -Wall -Wextra -fsanitize=address

scanner.o: scanner.c scanner.h
	gcc -c $(GCC_OPTIONS) scanner.c

klang: main.c scanner.o scanner.h
	gcc -o klang $(GCC_OPTIONS) main.c scanner.o

clean:
	rm klang *.o
