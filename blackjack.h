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
} Dealer;

typedef struct {
    char name[50];
    int score;
} PlayerScore;
void add_card_to_hand(Card** hand, Card* card);
int total_value(Card* hand);
int count_cards(Card* hand);
void playBlackjack(dek* stack);
void saveScoreToFile(Player *player);
void readScoresFromFile();
void reset_hand(Card** hand);

#endif // BLACKJACK_H
