#include "card.h"


int isEmpty(dek* stack)
{
    return stack->top == NULL;
}

void push(dek* stack, Card card)
{
    Card* Newnode = (Card*)malloc(sizeof(Card));
    if (Newnode == NULL)
    {
        printf("Gagal Alokasi Memori");
        exit(1);
    }
    Newnode->suit = card.suit;
    Newnode->rank = card.rank;
    Newnode->value = card.value;
    Newnode->next = stack->top;
    stack->top = Newnode;       
}

Card* pop(dek* stack) {
    if (isEmpty(stack)) {
        printf("The stack is empty\n");
        return NULL;
    }
    Card* topCard = stack->top;
    stack->top = stack->top->next;
    return topCard;
}

//pengisian nilai untuk kartu
int pengisian_nilai_kartu(Rank rank)
{
    switch(rank)
    {
        case JACK: case QUEEN: case KING: return 10;
        default: return rank;   
    }
}
//pembuatan dek

// Function to create and initialize a deck of cards
Card* create_deck() {
    Card* deck = NULL;
    Card* last_card = NULL;

    for (int suit = HEARTS; suit <= SPADES; ++suit) {
        for (int rank = ACE; rank <= KING; ++rank) {
            Card* new_card = (Card*)malloc(sizeof(Card));
            new_card->suit = (Suit)suit;
            new_card->rank = (Rank)rank;
            new_card->value = pengisian_nilai_kartu(new_card->rank);
            new_card->next = NULL;

            if (deck == NULL) {
                deck = new_card;
            } else {
                last_card->next = new_card;
            }
            last_card = new_card;
        }
    }
    return deck;
}