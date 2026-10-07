#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "game.h"

player_t newPlayer(int bankroll, int bet, int nbOfHands) {
    player_t p;
    p.bankroll = bankroll;
    p.nbOfHands = nbOfHands;
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
        int bet;
        printf("Place a bet for hand %d :", i+1);
        scanf("%d", &bet);
        p.hands[i].bet = bet;
        strcpy(p.hands[i].res, "");
        p.hands[i].gain = 0;
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
    //printf("hit\n");
    if (hand->nbOfCards < 10) { // Check if the hand has less than 10 cards
        hand->cards[hand->nbOfCards] = deck->card[deck->currentCard]; // Add the last card from the deck to the hand
        hand->nbOfCards++;
        deck->currentCard++; // Move to the next card in the deck
    } else {
        printf("Cannot hit, hand is full.\n");
    }
}

void doubledown(player_t *player, deck_t *deck) {
    //printf("doubledown\n");
    hand_t *hand=&(player->hands[player->currentHand]);
    hit(hand, deck);
    hand->isDoubledDown = 1;
    hand->isStanding = 1;
    printHand(*hand, player->currentHand);
    player->currentHand++;
}

void split(player_t *player, deck_t *deck) {
    printf("split\n");
    //if (hand->cards[0].val==hand->cards[1].val) {
        hand_t newHand;
        hand_t *hand=&(player->hands[player->currentHand]);
        newHand.cards[0]=hand->cards[1];
        hand->nbOfCards--;
        hand->isSplit=1;
        newHand.nbOfCards = 1;
        newHand.isBusted = 0;
        newHand.isStanding = 0;
        newHand.isDoubledDown = 0;
        newHand.isSplit = 1;  // hand->isSplit=1;
        hit(&newHand, deck);
        hit(hand, deck);
        player->hands[player->currentHand+1]=newHand;
        player->nbOfHands++;
    //}

}

void stay(player_t *player) {
    //printf("stay\n");
    player->hands[player->currentHand].isStanding = 1;
    player->currentHand++;
}

int cardValue(card_t card) {
    char val = card.val;
    if (val >= '2' && val <= '9') {
        return val - '0'; // Convert char to int
    } else if (val == 'T' || val == 'J' || val == 'Q' || val == 'K') {
        return 10;
    } else if (val == 'A') {
        return 11;
    }
    return 1;
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
void printHand(hand_t hand, int handIndex) {
    //printf("printHand\n");
    if (handIndex == -1) printf("Dealer hand: [ ");
    else  printf("Hand %d : [ ", handIndex+1);
    for (int i = 0; i < hand.nbOfCards; i++) {
        printCard(hand.cards[i]);
        if (i < hand.nbOfCards - 1) {
            printf(", ");
        }
    }
    printf(" ], Score : %d\n", handValue(hand));
}

void startHand(deck_t *deck, player_t *player, dealer_t *dealer) {
    printf("startHand\n");
    mixDeck(deck);
    for (int i = 0;i<player->nbOfHands;i++){
        hit(&player->hands[i], deck);
    }
    hit(&dealer->hand, deck);
    for (int i = 0;i<player->nbOfHands;i++){
        hit(&player->hands[i], deck);
    }
    hit(&dealer->hand, deck);
    printf("Hand's dealer.\n");
    printf("[ ");
    printCard(dealer->hand.cards[0]);
    printf(", XX ] Score : %d\n", cardValue(dealer->hand.cards[0])); // Print the score of the dealer's hand with one card hidden
    // printDeck(*deck); // Print the remaining cards in the deck
}

/*int isDealerTurn(player_t *player) {
    if (player_t->nbOfHands == player->currentHand && player->currentHand.isStanding) dealerTurn();
}*/

void playerTurn(deck_t *deck, player_t *player) {
    printf("playerTurn\n");
    printHand(player->hands[player->currentHand], player->currentHand);
    char action;
    hand_t *hand = &(player->hands[player->currentHand]);
    scanf(" %c", &action);
    switch (action) {
        case 'S' :
            split(player, deck);
            
            break;
        case 'H' :
            hit(hand, deck);
            break;
        case 'D' :
            doubledown(player, deck);
            break;
        case 'N' :
            stay(player);
            break;
    }
    
}


void updateAction(player_t *player) {
    if (player->currentHand == player->nbOfHands) return;
    printf("updateAction\n");
    hand_t *hand = &(player->hands[player->currentHand]);
    int score = handValue(*hand);
    if (score > 21) {
        hand->isBusted = 1;
        printHand(player->hands[player->currentHand], player->currentHand);
        player->currentHand++;
    }
    else if (score == 21) {
        if (hand->nbOfCards == 2 && hand->isSplit == 0) hand->isBlackjack = 1;
        else hand->isStanding = 1;
        printHand(player->hands[player->currentHand], player->currentHand);
        player->currentHand++;
    }

}


void dealerTurn(dealer_t *dealer, deck_t *deck) {
    printf("dealerTurn\n");
    while (handValue(dealer->hand) < 17) {
        hit(&(dealer->hand), deck);
    }
    if (handValue(dealer->hand) > 21) dealer->hand.isBusted = 1;
    printHand(dealer->hand, -1);
}
void getResult(player_t *player, dealer_t *dealer) {
    int dealerVal = handValue(dealer->hand);

    for (int i = 0; i < player->nbOfHands; i++) {
        int playerVal = handValue(player->hands[i]);

        
        if (player->hands[i].isBusted) {
            strcpy(player->hands[i].res, "loss");
        }
        
        else if (dealer->hand.isBusted) {
            strcpy(player->hands[i].res, "win");
            player->hands[i].gain = player->hands[i].bet*2;
        }
        
        else if (dealer->hand.isBlackjack || player->hands[i].isBlackjack) {
            if (dealer->hand.isBlackjack && player->hands[i].isBlackjack) {
                strcpy(player->hands[i].res, "tie");
                player->hands[i].gain = player->hands[i].bet;

            } else if (player->hands[i].isBlackjack) {
                strcpy(player->hands[i].res, "win");
                player->hands[i].gain = player->hands[i].bet*2.5;
            } else {
                strcpy(player->hands[i].res, "loss");
            }
        }
        
        else {
            if (playerVal > dealerVal) {
                strcpy(player->hands[i].res, "win");
                player->hands[i].gain = player->hands[i].bet*2;
            } else if (playerVal < dealerVal) {
                strcpy(player->hands[i].res, "loss");
            } else {
                strcpy(player->hands[i].res, "tie");
                player->hands[i].gain = player->hands[i].bet;
            }
        }
    }
}

int sumBet(player_t player) {
    int sum;
    for (int i=0; i<player.nbOfHands; i++) {
        sum+=player.hands[i].bet;
    }
    return sum;
}

int sumGain(player_t player) {
    int sum;
    for (int i=0; i<player.nbOfHands; i++) {
        sum+=player.hands[i].gain;
    }
    return sum;
}


void printResult(player_t player){
    for (int i=0; i<player.nbOfHands;i++){
        printf("Hand n°%d /", i+1);
        for (int j=0; j<strlen(player.hands[i].res); j++){
            printf("%c",player.hands[i].res[j]);
        }
        printf(" gain : %d", player.hands[i].gain);
        printf("\n");
    }
    int sumOfBets=sumBet(player);
    printf("sumOfBets = %d", sumOfBets);
    int sumOfGains=sumGain(player);
    printf("sumOfGains = %d", sumOfGains);
    if (sumOfBets < sumOfGains) printf("Total loss of %d\n", sumOfGains-sumOfBets);
    else printf("Total win of %d\n", sumOfGains-sumOfBets);
}

