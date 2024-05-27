#ifndef POINTS_H
#define POINTS_H

// Struktur untuk menyimpan informasi highscore
typedef struct {
    char name[50];
    int score;
} Highscore;

// Fungsi untuk menambahkan poin ke highscore
void addPointsToPlayer(Player *player, int points, int *winstreak);

// Fungsi untuk menangani kemenangan
void handleWin(Player *player, int basePoints, int *winstreak);

// Fungsi untuk menangani kekalahan
void handleLoss(int *winstreak) ;

// Fungsi untuk mencetak highscore
void printPlayerScore(const Player *player);

#endif // HIGHSCORE_H
