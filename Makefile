
compile:
	gcc -o trab3 main.c graph.c page.c rbt.c wordlist.c inputread.c -lm

run_p_1:
	./trab3 ./entradas/pequenos/1/ < ./entradas/pequenos/1/searches.txt

run_p_2:
	./trab3 ./entradas/pequenos/2/ < ./entradas/pequenos/2/searches.txt

run_p_3:
	./trab3 ./entradas/pequenos/3/ < ./entradas/pequenos/3/searches.txt

run_p_4:
	./trab3 ./entradas/pequenos/4/ < ./entradas/pequenos/4/searches.txt

run_g_1:
	./trab3 ./entradas/grandes/1/ < ./entradas/grandes/1/searches.txt

run_gg_1:
	./trab3 ./entradas/gigantes/1/ < ./entradas/gigantes/1/searches.txt

run_gg_2:
	./trab3 ./entradas/gigantes/2/ < ./entradas/gigantes/2/searches.txt
	
run_gg_3:
	./trab3 ./entradas/gigantes/3/ < ./entradas/gigantes/3/searches.txt

run_all:
	./trab3 ./entradas/pequenos/1/ < ./entradas/pequenos/1/searches.txt > ./entradas/pequenos/1/saida.txt
	./trab3 ./entradas/pequenos/2/ < ./entradas/pequenos/2/searches.txt > ./entradas/pequenos/2/saida.txt
	./trab3 ./entradas/pequenos/3/ < ./entradas/pequenos/3/searches.txt > ./entradas/pequenos/3/saida.txt
	./trab3 ./entradas/pequenos/4/ < ./entradas/pequenos/4/searches.txt > ./entradas/pequenos/4/saida.txt
	./trab3 ./entradas/grandes/1/ < ./entradas/grandes/1/searches.txt > ./entradas/grandes/1/saida.txt

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s ./trab3 ./entradas/pequenos/1/ < ./entradas/pequenos/1/searches.txt

valgrind_g:
	valgrind --leak-check=full --show-leak-kinds=all -s ./trab3 ./entradas/grandes/1/ < ./entradas/grandes/1/searches.txt

valgrind_gg:
	valgrind --leak-check=full --show-leak-kinds=all -s ./trab3 ./entradas/gigantes/3/ < ./entradas/gigantes/3/searches.txt

clean:
	rm trab3