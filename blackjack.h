#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "card.h"

typedef struct {
    Card* hand;
    char name[50];
    int score;
} Player;

typedef struct {
    Card* hand;
    int numCards;
} Dealer;

void add_card_to_hand(Card** hand, Card* card);
int total_value(Card* hand);
int count_cards(Card* hand);
void display_hand(Card* hand);
void playBlackjack(dek* stack);
#endif // BLACKJACK_H
