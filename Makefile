GCC_OPTIONS = -Wall -Wextra -fsanitize=address

klang: main.c
	gcc -o klang $(GCC_OPTIONS) main.c

clean:
	rm klang
