
compile:
	gcc -o trab3 main.c graph.c page.c rbt.c wordlist.c inputread.c -lm

run_teste10_1:
	./trab3 ./entradas/teste10_1/

run_teste10_2:
	./trab3 ./entradas/teste10_2/

run_teste30_1:
	./trab3 ./entradas/teste30_1/

run_teste30_2:
	./trab3 ./entradas/teste30_2/

run_teste50_1:
	./trab3 ./entradas/teste50_1/

run_teste50_2:
	./trab3 ./entradas/teste50_2/

run_teste100_1:
	./trab3 ./entradas/teste100_1/

run_teste100_2:
	./trab3 ./entradas/teste100_2/

run_TesteProfessor:
	./trab3 ./entradas/TesteProfessor/

run_testePTBR:
	./trab3 ./entradas/testePTBR/

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s ./trab3 ./entradas/teste100_2/ < palavras.txt

clean:
	rm trab3