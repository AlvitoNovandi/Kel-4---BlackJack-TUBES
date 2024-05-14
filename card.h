#include <stdlib.h> //malloc
#include <stdio.h>

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

void initializeStack(dek* stack);
void push(dek* stack, Card card);
Card* pop(dek* stack);
int pengisian_nilai_kartu(Rank rank);
Card* create_deck();
