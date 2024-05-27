#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan informasi highscore
typedef struct {
    char name[50];
    int score;
} Highscore;

// Fungsi untuk menambahkan poin ke highscore
void addPointsToHighscore(Highscore *highscore, const char *playerName, int points, int *winstreak) {
    if (points > 0) {
        // Jika ada winstreak, gandakan poin
        if (*winstreak > 1) {
            points *= 2;
        }
        // Update highscore
        strcpy(highscore->name, playerName);
        highscore->score += points;

        // Tampilkan informasi poin yang ditambahkan
        printf("Player %s mendapat %d poin! Total skor: %d\n", playerName, points, highscore->score);
    } else {
        printf("Player %s tidak mendapatkan poin.\n", playerName);
    }
}

// Fungsi untuk menangani kemenangan
void handleWin(Highscore *highscore, const char *playerName, int basePoints, int *winstreak) {
    (*winstreak)++;
    addPointsToHighscore(highscore, playerName, basePoints, winstreak);
}

// Fungsi untuk menangani kekalahan
void handleLoss(int *winstreak) {
    *winstreak = 0;
    printf("Anda kalah, winstreak direset.\n");
}

// Fungsi untuk mencetak highscore
void printHighscore(const Highscore *highscore) {
    printf("Highscore:\n");
    printf("Player: %s\n", highscore->name);
    printf("Score: %d\n", highscore->score);
}

int main() {
    Highscore highscore = {"", 0};
    int winstreak = 0;
    int basePoints = 10;  // Poin dasar per kemenangan

    // Simulasi permainan
    handleWin(&highscore, "Player", basePoints, &winstreak);  // Menang
    handleWin(&highscore, "Player", basePoints, &winstreak);  // Menang dengan winstreak
    handleLoss(&winstreak);  // Kalah
    handleWin(&highscore, "Player", basePoints, &winstreak);  // Menang

    // Cetak highscore akhir
    printHighscore(&highscore);

    return 0;
}
