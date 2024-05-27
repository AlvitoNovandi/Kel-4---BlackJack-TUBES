#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "card.h"

void add_card_to_hand(Card** hand, Card* card) {
    card->next = *hand;
    *hand = card;
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


int total_value(Card* hand) {
    int total = 0;
    while (hand != NULL) {
        total += hand->value;
        hand = hand->next;
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
void playBlackjack(dek* stack) {
    Player player = { NULL, 0 };
    Dealer dealer = { NULL, 0 };

    add_card_to_hand(&player.hand, pop(stack));
    add_card_to_hand(&player.hand, pop(stack));
    add_card_to_hand(&dealer.hand, pop(stack));
    add_card_to_hand(&dealer.hand, pop(stack));

    printf("Your cards:\n");
    display_hand(player.hand);
    printf("Dealer's cards:\n");
    display_hand(dealer.hand);


    char choice;
    while (total_value(player.hand) <= 21) {
        printf("Hit or stand? (h/s): ");
        scanf(" %c", &choice);
        if (choice == 'h') {
            add_card_to_hand(&player.hand, pop(stack));
            printf("Your cards:\n");
            display_hand(player.hand);
            printf("Dealer's cards:\n");
            display_hand(dealer.hand);
            
            if (total_value(player.hand) > 21) {
                printf("You bust!\n");
                return;
            }
        } else {
            break;
        }
    }

    while (total_value(dealer.hand) < 18) {
        add_card_to_hand(&dealer.hand, pop(stack));
    }

    printf("Your total: %d\nDealer's total: %d\n", total_value(player.hand), total_value(dealer.hand));

    if (total_value(player.hand) > 21) {
        printf("You lose!\n");
    } else if (total_value(dealer.hand) > 21) {
        printf("Dealer busts! You win!\n");
    } else if (total_value(player.hand) > total_value(dealer.hand)) {
        printf("You win!\n");
    } else if (total_value(player.hand) < total_value(dealer.hand)) {
        printf("You lose!\n");
    } else {
        printf("It's a tie!\n");
    }
        printf("Dealer's cards:\n");
    display_hand(dealer.hand);
}

int main() {
    printf("Welcome to Blackjack!\n");
    getchar(); // Tunggu sampai tombol Enter ditekan

    char playAgain = 'y';
    while (playAgain == 'y') {
        dek stack;
        initializeStack(&stack); // Inisialisasi tumpukan

        // Membuat dek, mengacaknya, dan mengisi tumpukan
        Card* deck = create_deck();
        int deckSize = hitung_kartu(deck);
        Card** deckArray = deck_to_array(deck, deckSize);
        shuffle_deck(deckArray, deckSize);

        // Menambahkan kartu yang sudah diacak ke dalam tumpukan
        for (int i = 0; i < deckSize; i++) {
            push(&stack, *deckArray[i]);
        }

        // Bebaskan memori
        free(deckArray);

        // Mulai permainan Blackjack
        playBlackjack(&stack);

        // Tanyakan apakah ingin bermain lagi
        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);
    }
    return 0;
}
