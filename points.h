#ifndef POINTS_H
#define POINTS_H

// Struktur untuk menyimpan informasi highscore
typedef struct {
    char name[50];
    int score;
} Highscore;

// Fungsi untuk menambahkan poin ke highscore
void addPointsToHighscore(Highscore *highscore, const char *playerName, int points, int *winstreak);

// Fungsi untuk menangani kemenangan
void handleWin(Highscore *highscore, const char *playerName, int basePoints, int *winstreak);

// Fungsi untuk menangani kekalahan
void handleLoss(int *winstreak);

// Fungsi untuk mencetak highscore
void printHighscore(const Highscore *highscore);

#endif // HIGHSCORE_H
