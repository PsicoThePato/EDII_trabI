all:
	gcc src/*.c -g -o trabI -Wall -ggdb3 -lm -pg -I /headers

run: all
	./trabI
