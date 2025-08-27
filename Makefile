.PHONY: clean
GCC_OPTIONS = -Wall -Wextra -fsanitize=address
GCC_DEBUG_OPTIONS = -Wall -Wextra

vector.o: vector.c vector.h
	gcc -c $(GCC_OPTIONS) vector.c

token.o: token.c token.h
	gcc -c $(GCC_OPTIONS) token.c

scanner.o: scanner.c scanner.h error.h
	gcc -c $(GCC_OPTIONS) scanner.c

klang: main.c scanner.o scanner.h vector.o vector.h token.o token.h
	gcc -o klang $(GCC_OPTIONS) main.c scanner.o vector.o token.o


d_vector.o: vector.c vector.h
	gcc -g -c -o d_vector.o $(GCC_DEBUG_OPTIONS) vector.c

d_token.o: token.c token.h
	gcc -g -c -o d_token.o $(GCC_DEBUG_OPTIONS) token.c

d_scanner.o: scanner.c scanner.h error.h
	gcc -g -c -o d_scanner.o $(GCC_DEBUG_OPTIONS) scanner.c

debug: main.c d_scanner.o scanner.h d_vector.o vector.h d_token.o token.h
	gcc -g -o klang $(GCC_DEBUG_OPTIONS) main.c d_scanner.o d_vector.o d_token.o


clean:
	rm klang *.o
