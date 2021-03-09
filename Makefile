all:
	gcc src/*.c -g -o trabI -Wall -ggdb3 -I /headers

run: all
	./trabI
