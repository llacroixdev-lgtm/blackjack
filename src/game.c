#include <stdio.h>
#include "deck.h"
#include "game.h"

player_t newPlayer(int bankroll, int bet) {
    player_t p;
    p.bankroll = bankroll;
    p.bet = bet;
    p.nbOfHands = 1;
    p.currentHand = 0; // Assuming the player starts with one hand
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

hand_t split(hand_t *hand, deck_t *deck) {
    if (hand->cards[0].val==hand->cards[1].val) {
        hand_t newHand;
        newHand.cards[0]=hand->cards[1];
        hand->nbOfCards--;
        newHand.nbOfCards = 1;
        hit(&newHand, deck);
        hit(hand, deck);
        newHand.isBusted = 0;
        newHand.isStanding = 0;
        newHand.isDoubledDown = 0;
        newHand.isSplit = 1;
        hand->isSplit=1;
        printHand(*hand);
        printHand(newHand);
        return newHand;
    }
    return *hand;
}
int handValue(hand_t hand) {
    int value = 0;
    int aces = 0;

    for (int i=0; i<hand.nbOfCards; i++) {
        char val = hand.cards[i].val;
        if (val >= '2' && val <= '9') {
            value += val - '0'; // Convert char to int
        } else if (val == 'T' || val == 'J' || val == 'Q' || val == 'K') {
            value += 10;
        } else if (val == 'A') {
            aces++;
            value += 11; // Initially count Ace as 11
        }
    }

    // Adjust for Aces if value is over 21
    while (value > 21 && aces > 0) {
        value -= 10; // Count one Ace as 1 instead of 11
        aces--;
    }

    return value;
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

void startHand(deck_t *deck, player_t *player, dealer_t *dealer) {
    mixDeck(deck);
    printDeck(*deck);
    for (int i = 0;i<player->nbOfHands;i++){
        hit(&player->hands[i], deck);
    }
    hit(&dealer->hand, deck);
    for (int i = 0;i<player->nbOfHands;i++){
        hit(&player->hands[i], deck);
    }
    hit(&dealer->hand, deck);
    printf("%d\n", dealer->hand.nbOfCards);
    printHand(player->hands[0]); // Print the player's hand
    printHand(dealer->hand); // Print the dealer's hand
    printDeck(*deck); // Print the remaining cards in the deck
}

void playerTurn(deck_t *deck, player_t *player, dealer_t *dealer) {
    char action;
    hand_t hand =player->hands[player->currentHand];
    scanf("%c", &action);
    switch (action) {
        case 'S' :
            split(&hand, deck);
            break;
        case 'H' :
            hit(&hand, deck);
        case 'D' :
            return ;
        case 'N' :
            return ;
    }
}

