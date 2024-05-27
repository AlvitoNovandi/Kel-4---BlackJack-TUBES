#include "blackjack.h"
#include "card.h"
#include "display_game.h"
#include "points.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void pauseForEnter() {
    printf("Press Enter to return to the menu...");
    while (getchar() != '\n'); // Clear any remaining newline character in the buffer
    getchar(); // Wait for the user to press Enter
}

int getValidMenuChoice() {
    int choice;
    char buffer[10];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &choice) == 1 && choice >= 1 && choice <= 3) {
                return choice;
            }
        }
        printf("Invalid input. Please enter a number between 1 and 3: ");
    }
}

int main() {
    int choice;
    
    
    welcome();

    do {
        displayMenu();
        choice = getValidMenuChoice();

        switch (choice) {
            case 1: {
                dek deck;
                Player player; // Declare player
                printf("Masukkan nama Anda: ");
                fgets(player.name, sizeof(player.name), stdin); // Use fgets to get the name
                strtok(player.name, "\n"); // Remove newline character from the name

                // Start the Blackjack game with the player's name
                initializeStack(&deck);
                deck.top = Semua_tentang_dek();
                printf("Selamat bermain, %s!\n", player.name);
                playBlackjack(&deck);
                free_deck(deck.top);
                break;
            }
            case 2:
                // Display scores
                readScoresFromFile(); // Read scores from file before displaying
                pauseForEnter(); // Wait for Enter key press before returning to menu
                break;
            case 3:
                printf("Terima kasih telah bermain!\n");
                sleep(2); // Wait 2 seconds before exiting the game
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                sleep(1); // Wait 1 second before returning to menu
        }
    } while (1);

    return 0;
}