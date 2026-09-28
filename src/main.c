#include <stdio.h>
#include <time.h>
#include "deck.h"
#include "game.h"
int  main () {
    srand(time(NULL));
    deck_t deck = newDeck(1);
    player_t player = newPlayer(1000, 50);
    dealer_t dealer = newDealer();

    startHand(&deck, &player, &dealer);
    playerTurn(&deck, &player, &dealer);


    return 0;
}