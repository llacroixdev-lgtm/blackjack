#include <stdio.h>
#include <time.h>
#include "deck.h"
int  main () {
    srand(time(NULL));
    deck_t deck = newDeck(1);
    deck_t deck2 = newDeck(2);
    mixDeck(&deck);
    mixDeck(&deck2);
    printDeck(deck);
    printDeck(deck2);
    return 0;
}