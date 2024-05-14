#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk kartu
typedef struct Card {
    char suit[10];    // Jenis kartu (hati, sekop, wajik, keriting)
    char rank[10];    // Nilai kartu (misalnya, 2, 3, 4, ..., 10, Jack, Queen, King, Ace)
    int value;        // Nilai numerik kartu dalam permainan blackjack
    struct Card* next; // Pointer ke kartu selanjutnya dalam linked list
} Card;

// Struktur data untuk tumpukan kartu di meja
typedef struct CardStack {
    Card* top; // Pointer ke kartu paling atas dalam tumpukan
    int size;  // Jumlah kartu dalam tumpukan
} CardStack;

// Struktur data untuk dealer
typedef struct Dealer {
    CardStack stack;  // Tumpukan kartu dealer di meja
    int points;       // Jumlah poin atau skor dealer
} Dealer;

// Struktur data untuk pemain
typedef struct Player {
    int points;     // Jumlah poin atau skor pemain
    Card* hand;     // Linked list kartu yang dipegang pemain
} Player;

#endif // BLACKJACK_H