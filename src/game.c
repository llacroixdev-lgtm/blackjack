#include <stdio.h>
#include "deck.h"
#include "game.h"

player_t newPlayer(int bankroll, int bet) {
    player_t p;
    p.bankroll = bankroll;
    p.bet = bet;
    p.nbOfHands = 1; // Assuming the player starts with one hand
    for (int i = 0; i < p.nbOfHands; i++) {
        p.hands[i].nbOfCards = 0;
        p.hands[i].isBlackjack = 0;
        p.hands[i].isBusted = 0;
        p.hands[i].isStanding = 0;
        p.hands[i].isDoubledDown = 0;
        p.hands[i].isSurrendered = 0;
        p.hands[i].isSplit = 0;
        p.hands[i].isInsured = 0;
    }
    return p;
}

dealer_t newDealer() {
    dealer_t d;
    d.hand.nbOfCards = 0;
    d.hand.isBlackjack = 0;
    d.hand.isBusted = 0;
    d.hand.isStanding = 0;
    return d;
}

void hit(hand_t *hand, deck_t *deck) {
    if (hand->nbOfCards < 10) { // Check if the hand has less than 10 cards
        hand->cards[hand->nbOfCards] = deck->card[deck->currentCard]; // Add the last card from the deck to the hand
        hand->nbOfCards++; // Increment the number of cards in the hand
        deck->currentCard++; // Move to the next card in the deck
    } else {
        printf("Cannot hit, hand is full.\n");
    }
}
void printHand(hand_t hand) {
    printf("Hand: [ ");
    for (int i = 0; i < hand.nbOfCards; i++) {
        printCard(hand.cards[i]);
        if (i < hand.nbOfCards - 1) {
            printf(", ");
        }
    }
    printf(" ]\n");
}

void startGame() {
    deck_t deck = newDeck(1);
    mixDeck(&deck);
    printDeck(deck);

    player_t player = newPlayer(1000, 50);
    dealer_t dealer = newDealer(); // Initialize dealer hand
    // Create a player with a bankroll of 1000 and a bet of 50
    for (int i = 0;i<player.nbOfHands;i++){
        hit(&player.hands[i], &deck);
    }
    hit(&dealer.hand, &deck);
    for (int i = 0;i<player.nbOfHands;i++){
        hit(&player.hands[i], &deck);
    }
    hit(&dealer.hand, &deck);
    printf("%d\n", dealer.hand.nbOfCards);
    printHand(player.hands[0]); // Print the player's hand
    printHand(dealer.hand); // Print the dealer's hand
    printDeck(deck); // Print the remaining cards in the deck

}

