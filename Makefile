all:
	gcc src/*.c -g -o trabI -Wall -ggdb3 -lm -I /headers

run: all
	./trabI
