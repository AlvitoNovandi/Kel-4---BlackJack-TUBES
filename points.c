#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "blackjack.h"
// Struktur untuk menyimpan informasi kartu
// typedef struct {
//     char suit[10];
//     char rank[5];
// } Card;

// // Struktur untuk menyimpan informasi pemain
// typedef struct {
//     Card* hand;
//     int numCards;
//     char name[50];
//     int score;
// } Player;

// Fungsi untuk menambahkan poin ke pemain
void addPointsToPlayer(Player *player, int points) {
    if (points > 0) {
        // Jika ada winstreak, gandakan poin
        if (*winstreak > 1) {
            points *= 2;
        }
        // Update skor pemain
        player->score += points;

        // Tampilkan informasi poin yang ditambahkan
        printf("Player %s mendapat %d poin! Total skor: %d\n", player->name, points, player->score);
    } else {
        printf("Player %s tidak mendapatkan poin.\n", player->name);
    }
}

// Fungsi untuk menangani kemenangan
void handleWin(Player *player, int basePoints) {
    player->score += basePoints;
    printf("Player %s mendapat %d poin! Total skor: %d\n", player->name, basePoints, player->score);
}

// Fungsi untuk menangani kekalahan
void handleLoss(Player *player) {
    printf("Anda kalah\n");
}



