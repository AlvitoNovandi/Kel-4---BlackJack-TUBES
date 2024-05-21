#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "card.h"
#include "card.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    Card* hand;
} Player;

typedef struct Dealer {
    Card* hand;
} Dealer;


void add_card_to_hand(Card** hand, Card* card);
int total_value(Card* hand);
int count_cards(Card* hand);
void display_hand(Card* hand);
void playBlackjack();
#endif 