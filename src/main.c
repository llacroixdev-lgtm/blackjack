#include <stdio.h>
#include <string.h>
#include <time.h>
#include "deck.h"
#include "game.h"
int  main () {
    srand(time(NULL));
    deck_t deck = newDeck(1);
    int nbOfHands;
    scanf("%d", &nbOfHands);
    player_t player = newPlayer(1000, 50, nbOfHands);
    dealer_t dealer = newDealer();

    startHand(&deck, &player, &dealer);
    updateAction(&player);
    while (player.currentHand < player.nbOfHands) {
        playerTurn(&deck, &player);
        updateAction(&player);
    }
    dealerTurn(&dealer, &deck);
    getResult(&player, &dealer);
    //printResult(&dealer, &player);
    return 0;
}