#include <stdio.h>
#define TABLE_SIZE 11

int h1(int key) {
    int x = (key + 7) * (key + 7);
    x = x / 16;
    x = x + key;
    x = x % TABLE_SIZE;
    return x;
}

void insert(int hash_table[], int key) {
    int hash_index = h1(key);
    int original_index = hash_index;
    int probe_count = 0;

    while (hash_table[hash_index] != -1) {
        printf("%d ", hash_index);
        hash_index = (hash_index + 1) % TABLE_SIZE;
        probe_count++;
        if (probe_count >= TABLE_SIZE) {
            printf("Table is full\n");
            return;
        }
    }
    printf("%d\n", hash_index);
    hash_table[hash_index] = key;
}

int main() {
    int hash_table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = -1;
    }

    int keys[] = {43, 23, 1, 0, 15, 31, 4, 7, 11, 3};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("Key\tHome Slot\tProbe Sequence\n");
    for (int i = 0; i < n; i++) {
        int home_slot = h1(keys[i]);
        printf("%d\t%d\t\t", keys[i], home_slot);
        insert(hash_table, keys[i]);
    }

    printf("\nFinal Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == -1)
            printf("Slot %d: Empty\n", i);
        else
            printf("Slot %d: %d\n", i, hash_table[i]);
    }

    return 0;
}