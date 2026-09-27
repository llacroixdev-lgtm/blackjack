#include <stdio.h>

typedef struct {
    card_t cards[10]; // Assuming a max of 1O cards in a hand} hand_t;
    int nbOfCards; // Number of cards in the hand
    int isBlackjack;
    int isBusted;
    int isStanding;
    int isDoubledDown;
    int isSurrendered;
    int isSplit;
    int isInsured; // All my boolean for a hand, to know if the player has done a specific action with this hand
} hand_t;

typedef struct {
    int bankroll;
    int bet;
    int nbOfHands; // Number of hands the player has
    hand_t hands[4]; // Assuming a max of 4 hands per player, for now ...
} player_t;

typedef struct {
    hand_t hand;
} dealer_t;

player_t newPlayer(int bankroll, int bet);
void hit(hand_t *hand, deck_t *deck);
void printHand(hand_t hand);
void startGame();

dealer_t newDealer();