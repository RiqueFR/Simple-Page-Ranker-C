compile:
	gcc -o trab3 *.c -lm

run:
	./trab3 ./entrada/

valgrind:
	valgrind ./trab3 ./entrada/