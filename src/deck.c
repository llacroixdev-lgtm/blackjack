#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deck.h"

char familleV[4]={'S', 'C', 'H', 'D'};
char valV[13]={'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

void fillDeck(deck_t *deck) {
    for (int n = 0; n < deck->nbOfDeck; n++) { // Ajoute un nombre de cartes correspondant au nombre de deck demandé.
        for (int i = 0; i < 4; i++) { 
            for (int j = 0; j < 13; j++) {
                deck->card[(i * 13 + j)+n*DECKOFCARDS].famille = familleV[i]; // indice = Pour chaque famille, on ajoute 13 cartes (i*13+j) + n*DECKOFCARDS pour ajouter les cartes du deck suivant.
                deck->card[(i * 13 + j)+n*DECKOFCARDS].val = valV[j];
            }
        }
    }
}

deck_t newDeck (int nbOfDeck) {
    deck_t d;
    d.nbOfDeck=nbOfDeck;
    d.nbOfCards=DECKOFCARDS*nbOfDeck;
    d.currentCard=0;
    fillDeck(&d);
    return d;
}

void printCard(card_t c) {
    printf("%c%c", c.famille, c.val);
}

void printDeck(deck_t d) {
    printf("Number of deck used : %d\n", d.nbOfDeck);
    printf("[ ");
    for (int i=d.currentCard; i<d.nbOfCards-1; i++) {
        printCard(d.card[i]);
        printf(", ");
    }
    printCard(d.card[d.nbOfCards-1]);
    printf("]\n");
}

void mixDeck(deck_t *deck) {
    for (int i = 0; i < deck->nbOfCards-1; i++) { // On parcourt toutes les cartes du deck.
        int j = rand() % ((deck->nbOfCards-1) - i+1)+i; // On choisit un indice aléatoire pour mélanger les cartes.
        card_t temp = deck->card[i]; // echange classique de deux cartes
        deck->card[i] = deck->card[j];
        deck->card[j] = temp;
    }
}

void remixDeck(deck_t * deck) {
    if (deck->currentCard > deck->nbOfCards/3*2)
    deck -> currentCard = 0;
    mixDeck(deck);
}

int isEmptyDeck(deck_t * deck){
    return (deck->nbOfCards-deck->currentCard > 0) ? 0 : 1;
}


