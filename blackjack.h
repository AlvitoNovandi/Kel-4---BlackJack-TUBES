#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definisi enum dan struktur
typedef enum {
    HEARTS = 1, DIAMONDS, CLUBS, SPADES
} Suit;

typedef enum {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

typedef struct Card {
    Suit suit;
    Rank rank;
    int value;
    struct Card* next;
} Card;

typedef struct {
    Card* top;
} dek;

typedef struct Player {
    Card* hand;
} Player;

typedef struct Dealer {
    Card* hand;
} Dealer;

// Deklarasi fungsi
void initializeStack(dek* stack);
void push(dek* stack, Card* card);
Card* pop(dek* stack);
int pengisian_nilai_kartu(Rank rank);
Card* create_deck();
void shuffle_deck(Card** deck);
void add_card_to_hand(Card** hand, Card* card);
int total_value(Card* hand);
int count_cards(Card* hand);
void display_hand(Card* hand);
void playBlackjack();
#endif 