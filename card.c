#include "card.h"

int isEmpty(dek* stack)
{
    return stack->top == NULL;
}

void push(dek* stack, Card card)
{
    Card* Newnode = (Card*)malloc(sizeof(Card));
    if (Newnode == NULL)
    {
        printf("Gagal Alokasi Memori");
        exit(1);
    }
    Newnode->suit = card.suit;
    Newnode->rank = card.rank;
    Newnode->value = card.value;
    Newnode->next = stack->top;
    stack->top = Newnode;       
}

Card* pop(dek* stack) {
    if (isEmpty(stack)) {
        printf("The stack is empty\n");
        return NULL;
    }
    Card* topCard = stack->top;
    stack->top = stack->top->next;
    return topCard;
}

void initializeStack(dek* stack) {
    stack->top = NULL;
}

//pengisian nilai untuk kartu
int pengisian_nilai_kartu(Rank rank)
{
    switch(rank)
    {
        case JACK: case QUEEN: case KING: return 10;
        default: return rank;   
    }
}

// Function to create and initialize a deck of cards
Card* create_deck() {
    Card* deck = NULL;
    Card* last_card = NULL;

    for (int suit = HEARTS; suit <= SPADES; ++suit) {
        for (int rank = ACE; rank <= KING; ++rank) {
            Card* new_card = (Card*)malloc(sizeof(Card));
            new_card->suit = (Suit)suit;
            new_card->rank = (Rank)rank;
            new_card->value = pengisian_nilai_kartu(new_card->rank);
            new_card->next = NULL;

            if (deck == NULL) {
                deck = new_card;
            } else {
                last_card->next = new_card;
            }
            last_card = new_card;
        }
    }
    return deck;
}

//print untuk pengujian
void print_deck(Card* deck) {
    Card* current_card = deck;
    while (current_card != NULL) {
        printf("Suit: %d, Rank: %d, Value: %d\n", current_card->suit, current_card->rank, current_card->value);
        current_card = current_card->next;
    }
}

//menghapus dek
void free_deck(Card* deck) {
    Card* current_card = deck;
    while (current_card != NULL) {
        Card* next_card = current_card->next;
        free(current_card);
        current_card = next_card;
    }
}

// fungsi menghitung jumlah kartu (untuk convert ke array)
int hitung_kartu(Card* deck) {
    int count = 0;
    Card* current = deck;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//fungsi mengubah linked list menjadi array
Card** deck_to_array(Card* deck, int size) {
    Card** array = (Card**)malloc(size * sizeof(Card*));  // Alokasi memori untuk array pointer Card
    Card* current = deck;  //current menunjuk ke dek
    for (int i = 0; i < size; i++) {
        array[i] = current;  // memasukkan linked list yang ditunjuk oleh current ke array
        current = current->next;  // Pindah ke kartu berikutnya dalam linked list
    }
    return array;  // Kembalikan array pointer
}

// mengacak array
void shuffle_deck(Card** array, int size) {
    srand(time(NULL));  // Seed generator nomor acak dengan waktu saat ini
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Hasilkan indeks acak j sehingga 0 <= j <= i
        // Tukar array[i] dengan array[j]
        Card* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//  mengembalikan array menjadi linked list lagi
Card* array_to_deck(Card** array, int size) {
    for (int i = 0; i < size - 1; i++) {
        array[i]->next = array[i + 1];  // Atur pointer next dari setiap kartu ke kartu berikutnya dalam array
    }
    array[size - 1]->next = NULL;  // Kartu terakhir menunjuk ke NULL
    return array[0];  // Kembalikan kepala daftar tertaut
}
