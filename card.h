#ifndef CARD_H
#define CARD_H

#include <stdlib.h> //malloc
#include <stdio.h>
#include <time.h> //rand

typedef enum
{
    HEARTS = 1,DIAMONDS,CLUBS,SPADES
}Suit;

typedef enum
{
    ACE = 1, TWO ,THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
}Rank;

typedef struct Card {
    Suit suit;
    Rank rank;
    int value;
    struct Card* next;
} Card;

typedef struct {
    Card* top;
} dek;

int isEmpty(dek* stack);
void push(dek* stack, Card card);
Card* pop(dek* stack);
void initializeStack(dek* stack);
int pengisian_nilai_kartu(Rank rank);
Card* create_deck();
void print_deck_kartu(Card* deck);
void free_deck(Card* deck);
int hitung_kartu(Card* deck);
Card** deck_to_array(Card* deck, int size);
void shuffle_deck(Card** array, int size);
Card* array_to_deck(Card** array, int size);
Card* Semua_tentang_dek();
void print_dealer(Player* head);

#endif //CARD_H