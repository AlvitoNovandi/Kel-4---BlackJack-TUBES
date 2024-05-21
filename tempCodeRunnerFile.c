// Fungsi untuk memasang taruhan
int placeBet(int playerMoney) {
    int betAmount;
    do {
        printf("Masukkan jumlah taruhan Anda: ");
        scanf("%d", &betAmount);
        if (betAmount <= 0) {
            printf("Jumlah taruhan tidak valid. Silakan masukkan nilai positif.\n");
        } else if (betAmount > playerMoney) {
            printf("Dana tidak mencukupi. Saldo Anda saat ini adalah %d.\n", playerMoney);
        }
    } while (betAmount <= 0 || betAmount > playerMoney);
    return betAmount;
}

int winStreak = 0; // Variabel untuk melacak winstreak

// Fungsi untuk memperbarui jumlah uang pemain berdasarkan hasil permainan
int updateMoney(int playerMoney, int betAmount, char result) {
    // Jika pemain menang
    if (result == 'w') {
        playerMoney += betAmount; // Menambahkan kemenangan ke jumlah uang pemain
        winStreak++; // Menambahkan winstreak
        // Jika winstreak mencapai 2, kemenangan berikutnya akan dua kali lipat
        if (winStreak == 2) {
            playerMoney += betAmount; // Menambahkan kemenangan ekstra
            printf("Selamat! Win streak Anda menggandakan kemenangan Anda!\n");
            winStreak = 0; // Mengatur kembali winstreak menjadi 0 setelah mencapai 2 winstreak
        }
    } 
    // Jika pemain kalah
    else if (result == 'l') {
        playerMoney -= betAmount; // Mengurangi jumlah taruhan dari jumlah uang pemain
        winStreak = 0; // Mengatur kembali winstreak menjadi 0 setelah kalah
    }
    return playerMoney;
}


// Fungsi untuk menampilkan jumlah uang pemain sebelum dan sesudah memasang taruhan
void displayMoney(int initialMoney, int finalMoney) {
    printf("Uang Awal: %d\n", initialMoney);
    printf("Uang Akhir: %d\n", finalMoney);
}