blackjack: src/main.o src/deck.o src/game.o
	gcc -o blackjack src/main.o src/deck.o src/game.o

src/main.o: src/main.c src/deck.h src/game.h
	gcc -c src/main.c -o src/main.o

src/deck.o: src/deck.c src/deck.h
	gcc -c src/deck.c -o src/deck.o

src/game.o: src/game.c src/game.h src/deck.h
	gcc -c src/game.c -o src/game.o

web: src/deck.c src/game.c src/wasm_api.c src/deck.h src/game.h
	mkdir -p web
	emcc src/deck.c src/game.c src/wasm_api.c -o web/blackjack.js -sEXPORTED_RUNTIME_METHODS=cwrap

clean:
	rm -f src/main.o src/deck.o src/game.o blackjack web/blackjack.js web/blackjack.wasm

run: blackjack
	./blackjack

.PHONY: clean run web