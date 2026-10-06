blackjack: src/main.o src/deck.o src/game.o
	gcc -o blackjack src/main.o src/deck.o src/game.o

src/main.o: src/main.c src/deck.h src/game.h
	gcc -c src/main.c -o src/main.o

src/deck.o: src/deck.c src/deck.h
	gcc src/deck.c -o src/deck.o

src/game.o: src/game.c src/game.h src/deck.h
	gcc -c src/game.c -o src/game.o

clean:
	rm -f src/main.o src/deck.o src/game.o blackjack

.PHONY: clean

run : blackjack
	./blackjack

