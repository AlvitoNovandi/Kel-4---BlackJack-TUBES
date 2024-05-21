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

void initializeStack(dek* stack) {
    stack->top = NULL;
}

int isEmpty(dek* stack) {
    return stack->top == NULL;
}

void push(dek* stack, Card* card) {
    card->next = stack->top;
    stack->top = card;
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

int pengisian_nilai_kartu(Rank rank) {
    switch(rank) {
        case JACK: case QUEEN: case KING: return 10;
       
        default: return rank;
    }
}

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

void shuffle_deck(Card** deck) {
    Card* array[52];
    Card* current = *deck;
    int count = 0;

    while (current != NULL) {
        array[count++] = current;
        current = current->next;
    }

    srand(time(NULL));
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52;
        Card* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    *deck = array[0];
    current = *deck;
    for (int i = 1; i < 52; i++) {
        current->next = array[i];
        current = current->next;
    }
    current->next = NULL;
}

void add_card_to_hand(Card** hand, Card* card) {
    card->next = *hand;
    *hand = card;
}

int total_value(Card* hand) {
    int total = 0;
    Card* current = hand;
    while (current != NULL) {
        total += current->value;
        current = current->next;
    }
    return total;
}

int count_cards(Card* hand) {
    int count = 0;
    Card* current = hand;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void display_hand(Card* hand) {
    Card* current = hand;
    while (current != NULL) {
        switch (current->rank) {
            case ACE: printf("Ace of "); break;
            case TWO: printf("2 of "); break;
            case THREE: printf("3 of "); break;
            case FOUR: printf("4 of "); break;
            case FIVE: printf("5 of "); break;
            case SIX: printf("6 of "); break;
            case SEVEN: printf("7 of "); break;
            case EIGHT: printf("8 of "); break;
            case NINE: printf("9 of "); break;
            case TEN: printf("10 of "); break;
            case JACK: printf("Jack of "); break;
            case QUEEN: printf("Queen of "); break;
            case KING: printf("King of "); break;
        }
        switch (current->suit) {
            case HEARTS: printf("Hearts\n"); break;
            case DIAMONDS: printf("Diamonds\n"); break;
            case CLUBS: printf("Clubs\n"); break;
            case SPADES: printf("Spades\n"); break;
        }
        current = current->next;
    }
    printf("\n");
}

void playBlackjack() {
    dek stack;
    initializeStack(&stack);

    Card* deck = create_deck();
    // shuffle_deck(&deck);

    while (deck != NULL) {
        Card* card = deck;
        deck = deck->next;
        push(&stack, card);
    }

    Player player = {NULL};
    Dealer dealer = {NULL};

    add_card_to_hand(&player.hand, pop(&stack));
    add_card_to_hand(&player.hand, pop(&stack));
    add_card_to_hand(&dealer.hand, pop(&stack));
    add_card_to_hand(&dealer.hand, pop(&stack));

    printf("Your cards:\n");
    display_hand(player.hand);
    printf("Dealer's cards:\n");
    display_hand(dealer.hand);

    char choice;
    while (1) {
        printf("\nHit (h) or Stand (s): ");
        scanf(" %c", &choice);

        if (choice == 'h') {
            add_card_to_hand(&player.hand, pop(&stack));
            printf("Your cards:\n");
            display_hand(player.hand);
            printf("Dealer's cards:\n");
            display_hand(dealer.hand);
            if (total_value(player.hand) > 21) {
                printf("Busted! You lose.\n");
                return;
            }
        } else if (choice == 's') {
            break;
        }
    }

    while (total_value(dealer.hand) < 17) {
        add_card_to_hand(&dealer.hand, pop(&stack));
    }

    printf("Your total: %d\nDealer's total: %d\n", total_value(player.hand), total_value(dealer.hand));

    if (total_value(player.hand) > 21 && total_value(dealer.hand) > 21) {
        if (total_value(player.hand) < total_value(dealer.hand)) {
            printf("Both busted! You win by being closer to 21.\n");
        } else if (total_value(dealer.hand) < total_value(player.hand)) {
            printf("Both busted! Dealer wins by being closer to 21.\n");
        } else {
            printf("Both busted and equally close! ");
            if (count_cards(player.hand) < count_cards(dealer.hand)) {
                printf("Dealer wins with fewer cards.\n");
            } else {
                printf("You win with fewer cards.\n");
            }
        }
    } else if (total_value(player.hand) > 21) {
        printf("Busted! You lose.\n");
    } else if (total_value(dealer.hand) > 21) {
        printf("Dealer busted! You win.\n");
    } else if (total_value(player.hand) > total_value(dealer.hand)) {
        printf("You win!\n");
    } else if (total_value(dealer.hand) > total_value(player.hand)) {
        printf("Dealer wins!\n");
    } else {
        printf("It's a draw! ");
        if (count_cards(player.hand) < count_cards(dealer.hand)) {
            printf("Dealer wins with fewer cards.\n");
        } else {
            printf("You win with fewer cards.\n");
        }
    }

    printf("\nDealer's cards:\n");
    display_hand(dealer.hand);
}


int main() {
    char playAgain;
    do {
        printf("Welcome to Blackjack!\n");
        printf("Press Enter to play the game...");
        getchar(); // Wait for Enter key
        getchar(); // Consume newline character

        playBlackjack();

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y');

    return 0;
}