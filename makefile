blackjack: src/main.o src/deck.o
	gcc -o blackjack src/main.o src/deck.o

src/main.o: src/main.c src/deck.h
	gcc -c src/main.c -o src/main.o

src/deck.o: src/deck.c src/deck.h
	gcc -c src/deck.c -o src/deck.o

clean:
	rm -f src/main.o src/deck.o blackjack

.PHONY: clean