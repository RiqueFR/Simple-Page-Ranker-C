compile:
	gcc -o trab3 main.c graph.c page.c trie.c wordlist.c inputread.c -lm

run:
	./trab3 ./entrada/

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./trab3 entrada/

clean:
	rm trab3