#include <stdio.h>
#include <stdlib.h>

#define DECKOFCARDS 52
#define MAX_CARDS 416

typedef struct {
    char famille;
    char val;
} card_t;


typedef struct {
    int nbOfDeck;
    int cardsLength;
    card_t card[MAX_CARDS];
} deck_t;

void fillDeck(deck_t *deck);
deck_t newDeck (int nbOfDeck);
void printCard(card_t c);
void printDeck(deck_t d);
void mixDeck(deck_t *deck);