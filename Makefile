build:
	gcc -Wall -g -o tema3  main.c functiiTema.c trie.c

clean:
	rm tema3

run:
	./tema3 input.txt output.txt

valgrind:
	valgrind --leak-check=yes --vgdb=no --track-origins=yes ./tema3 input.txt output.txt