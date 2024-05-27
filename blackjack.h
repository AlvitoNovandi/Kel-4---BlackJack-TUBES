#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "card.h"

typedef struct {
    Card* hand;
    int numCards;
} Player;

typedef struct {
    Card* hand;
    int numCards;
} Dealer;

void shuffle_deck(Card** array, int size); // Konsisten dengan card.h
void add_card_to_hand(Card** hand, Card* card);
int total_value(Card* hand);
int count_cards(Card* hand);
void display_hand(Card* hand);
void playBlackjack(dek* stack);
#endif // BLACKJACK_H
