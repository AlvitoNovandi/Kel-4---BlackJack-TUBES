#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan informasi kartu
typedef struct {
    char suit[10];
    char rank[5];
} Card;

// Struktur untuk menyimpan informasi pemain
typedef struct {
    Card* hand;
    int numCards;
    char name[50];
    int score;
} Player;

// Fungsi untuk menambahkan poin ke pemain
void addPointsToPlayer(Player *player, int points, int *winstreak) {
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
void handleWin(Player *player, int basePoints, int *winstreak) {
    (*winstreak)++;
    addPointsToPlayer(player, basePoints, winstreak);
}

// Fungsi untuk menangani kekalahan
void handleLoss(int *winstreak) {
    *winstreak = 0;
    printf("Anda kalah, winstreak direset.\n");
}

// Fungsi untuk mencetak skor pemain
void printPlayerScore(const Player *player) {
    printf("Highscore:\n");
    printf("Player: %s\n", player->name);
    printf("Score: %d\n", player->score);
}

int main() {
    Player player;
    player.hand = NULL;
    player.numCards = 0;
    strcpy(player.name, "Player");
    player.score = 0;

    int winstreak = 0;
    int basePoints = 10;  // Poin dasar per kemenangan

    // Simulasi permainan
    handleWin(&player, basePoints, &winstreak);  // Menang
    handleWin(&player, basePoints, &winstreak);  // Menang dengan winstreak
    handleLoss(&winstreak);  // Kalah
    handleWin(&player, basePoints, &winstreak);  // Menang

    // Cetak highscore akhir
    printPlayerScore(&player);

    return 0;
}
