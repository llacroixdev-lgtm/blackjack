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
    int isInsured;
    char res[5]; // All my boolean for a hand, to know if the player has done a specific action with this hand
} hand_t;

typedef struct {
    int bankroll;
    int bet;
    int nbOfHands; // Number of hands the player has
    hand_t hands[4];
    int currentHand; // Assuming a max of 4 hands per player, for now ...
} player_t;

typedef struct {
    hand_t hand;
} dealer_t;

player_t newPlayer(int bankroll, int bet, int nbOfHands);
void stay(player_t *player);
void hit(hand_t *hand, deck_t *deck);
void doubledown(player_t *player, deck_t *deck);
void split(player_t *player, deck_t *deck);
void printHand(hand_t hand);
int cardValue(card_t card);
int handValue(hand_t hand);

void startHand(deck_t *deck, player_t *player, dealer_t *dealer);

void playerTurn(deck_t *deck, player_t *player);
void updateAction(player_t *player);
void dealerTurn(dealer_t *dealer, deck_t *deck);
void getResult(player_t *player, dealer_t *dealer);
dealer_t newDealer();