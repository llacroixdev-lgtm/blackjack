#include <stdio.h>
#include <string.h>
#include <time.h>
#include "deck.h"
#include "game.h"
int  main () {
    srand(time(NULL));
    deck_t deck = newDeck(1);
    mixDeck(&deck);
    player_t player = newPlayer(1000);
    dealer_t dealer = newDealer();
    while (player.bankroll > 0 && !isEmptyDeck(&deck)) {
        newPlayerHand(&player);
        handPlay(&deck, &player, &dealer);
        player.currentHand=0;
        dealer.hand=createHand();
        remixDeck(&deck);
    }
    return 0;
}