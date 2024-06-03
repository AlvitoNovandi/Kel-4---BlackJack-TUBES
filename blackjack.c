#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "card.h"

void add_card_to_hand(Card** hand, Card* card) {
    card->next = *hand;
    *hand = card;
}


// Fungsi untuk membandingkan skor dua pemain (untuk qsort)
int compareScores(const void *a, const void *b) {
    PlayerScore *scoreA = (PlayerScore *)a;
    PlayerScore *scoreB = (PlayerScore *)b;
    return scoreB->score - scoreA->score;
}

void readScoresFromFile_topscore() {
    FILE *file = fopen("scores.txt", "r"); // Buka file untuk membaca

    if (file != NULL) {
        printf("Skor pemain yang tersimpan:\n");
        PlayerScore scores[100]; // Array untuk menyimpan skor, asumsikan maksimum 100 skor
        int count = 0;
        char line[100]; // Ukuran buffer yang mencukupi untuk membaca satu baris

        while (fgets(line, sizeof(line), file) != NULL) { // Baca satu baris pada setiap iterasi
            if (count < 100) { // Pastikan tidak melebihi ukuran array
                if (sscanf(line, "%[^,],%d", scores[count].name, &scores[count].score) == 2) {
                    count++;
                } else {
                    printf("Format file tidak valid: %s\n", line);
                }
            } else {
                printf("Melebihi kapasitas array, beberapa skor mungkin tidak terbaca.\n");
                break;
            }
        }
        fclose(file); // Tutup file setelah selesai membaca

        // Urutkan skor dari yang terbesar ke terkecil
        qsort(scores, count, sizeof(PlayerScore), compareScores);

        // Tampilkan 10 skor teratas atau kurang jika kurang dari 10
        for (int i = 0; i < count && i < 10; i++) {
            printf("Player: %s, Score: %d\n", scores[i].name, scores[i].score);
        }
    } else {
        printf("Gagal membuka file untuk membaca skor.\n");
    }
}

void saveScoreToFile(Player *player) {
    FILE *file = fopen("scores.txt", "a"); // Append mode

    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "%s,%d\n", player->name, player->score); // Menulis nama dan skor ke file dengan koma sebagai pemisah
    fclose(file);
}

void readScoresFromFile() {
    FILE *file = fopen("scores.txt", "r"); // Buka file untuk membaca

    if (file != NULL) {
        printf("Skor pemain yang tersimpan:\n");
        char line[100]; // Ukuran buffer yang mencukupi untuk membaca satu baris
        while (fgets(line, sizeof(line), file) != NULL) { // Baca satu baris pada setiap iterasi
            char name[50];
            int score;
            // Memisahkan nama pemain dan skor dari baris yang dibaca
            if (sscanf(line, "%[^,],%d", name, &score) == 2) {
                printf("Player: %s, Score: %d\n", name, score);
            } else {
                printf("Format file tidak valid: %s\n", line);
            }
        }
        fclose(file); // Tutup file setelah selesai membaca
    } else {
        printf("Gagal membuka file untuk membaca skor.\n");
    }
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

void reset_hand(Card** hand) {
    Card* current = *hand;
    while (current != NULL) {
        Card* temp = current;
        current = current->next;
        free(temp); // Membebaskan memori setiap node
    }
    *hand = NULL; // Atur pointer tangan ke NULL setelah semua kartu dihapus
}



void playBlackjack(dek* stack) {
    Player player = { NULL, 0 };
    Dealer dealer = { NULL, 0 };
    char playAgain;
    printf("Masukkan nama Anda: ");
    scanf("%s", player.name);
    printf("Selamat bermain, %s!\n", player.name);
    do {
        

        // Deal initial cards
        add_card_to_hand(&player.hand, pop(stack));
        add_card_to_hand(&player.hand, pop(stack));
        add_card_to_hand(&dealer.hand, pop(stack));
        add_card_to_hand(&dealer.hand, pop(stack));

        printf("kartu Kamu:\n");
        print_deck_kartu(player.hand);
        printf(" Kartu Dealer:\n");
        print_dealer(dealer.hand);

        char choice;
        while (total_value(player.hand) <= 21) {
            printf("Hit or stand? (h/s): ");
            scanf(" %c", &choice);
            if (choice == 'h') {
                add_card_to_hand(&player.hand, pop(stack));
                printf("Kartu Kamu:\n");
                print_deck_kartu(player.hand);
                printf(" Kartu Dealer:\n");
                print_dealer(dealer.hand);

                if (total_value(player.hand) > 21) {
                    printf("You bust!\n");
                    you_lose();
                    handleLoss(&player);
                    printf("Kartu Kamu:\n");
                    print_deck_kartu(player.hand);
                    printf(" Kartu Dealer:\n");
                    print_deck_kartu(dealer.hand);
                    printf("total kamu: %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));
                   
                    break;
                }
            } else {
                break;
            }
        }

        if (total_value(player.hand) <= 21) {
            
            while (total_value(dealer.hand) < 18) {
                add_card_to_hand(&dealer.hand, pop(stack));
                    printf("Kartu Kamu:\n");
                    print_deck_kartu(player.hand);
                    printf(" Kartu Dealer:\n");
                    print_deck_kartu(dealer.hand);
                    printf("total kamu: %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));
            }

            printf("total kamu: %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));

            if (total_value(dealer.hand) > 21) {
                printf("Dealer busts! You win!\n");
                you_win();
                printf("Kartu Kamu:\n");
                print_deck_kartu(player.hand);
                printf(" Kartu Dealer:\n");
                print_deck_kartu(dealer.hand);
                
                printf("total kamu: %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));
                handleWin(&player, 10);
                
            } else if (total_value(player.hand) > total_value(dealer.hand)) {
                printf("You win!\n");
                you_win();
                printf("Kartu Kamu:\n");
                print_deck_kartu(player.hand);
                printf(" Kartu Dealer:\n");
               print_deck_kartu(dealer.hand);
                
                printf("total kamu: %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));
                handleWin(&player, 10);
                
            } else if (total_value(player.hand) < total_value(dealer.hand)) {
                printf("You lose!\n");
                you_lose();
                 printf("Kartu Kamu:\n");
                print_deck_kartu(player.hand);
                printf(" Kartu Dealer:\n");
               print_deck_kartu(dealer.hand);
                handLoss(&player);
                printf("total kamu: %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));
                
            } else {
                printf("It's a tie!\n");
                draw();
                printf("Kartu Kamu:\n");
                print_deck_kartu(player.hand);
                printf(" Kartu Dealer:\n");
                print_deck_kartu(dealer.hand);
                printf(": %d\nDealer total: %d\n", total_value(player.hand), total_value(dealer.hand));
            }
        }

        printf("Mau Main Lagi (y/n): ");
        scanf(" %c", &playAgain);
        if (playAgain != 'y' && playAgain != 'Y') {
            saveScoreToFile(&player); // Menyimpan skor pemain saat menang
            break;
        }

        // Reset hands for the next round
        reset_hand(&player.hand);
        reset_hand(&dealer.hand);

    } while (1);
}
