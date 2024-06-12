#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int map[26] = {0};
    int i, j, k = 0, keyLen = strlen(key);

    for (i = 0; i < keyLen; i++) {
        if (key[i] == 'J') {
            key[i] = 'I';
        }
        if (!map[key[i] - 'A']) {
            keyTable[k / SIZE][k % SIZE] = key[i];
            map[key[i] - 'A'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i + 'A' == 'J') {
            continue;
        }
        if (!map[i]) {
            keyTable[k / SIZE][k % SIZE] = i + 'A';
            k++;
        }
    }
}

void search(char keyTable[SIZE][SIZE], char a, char b, int pos[]) {
    int i, j;

    if (a == 'J') a = 'I';
    if (b == 'J') b = 'I';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                pos[0] = i;
                pos[1] = j;
            }
            if (keyTable[i][j] == b) {
                pos[2] = i;
                pos[3] = j;
            }
        }
    }
}

void decryptPair(char keyTable[SIZE][SIZE], char pair[2], char decryptedPair[2]) {
    int pos[4];
    search(keyTable, pair[0], pair[1], pos);

    if (pos[0] == pos[2]) {
        decryptedPair[0] = keyTable[pos[0]][(pos[1] + SIZE - 1) % SIZE];
        decryptedPair[1] = keyTable[pos[2]][(pos[3] + SIZE - 1) % SIZE];
    } else if (pos[1] == pos[3]) {
        decryptedPair[0] = keyTable[(pos[0] + SIZE - 1) % SIZE][pos[1]];
        decryptedPair[1] = keyTable[(pos[2] + SIZE - 1) % SIZE][pos[3]];
    } else {
        decryptedPair[0] = keyTable[pos[0]][pos[3]];
        decryptedPair[1] = keyTable[pos[2]][pos[1]];
    }
}

void decryptMessage(char keyTable[SIZE][SIZE], char ciphertext[], char plaintext[]) {
    int len = strlen(ciphertext);
    char pair[2], decryptedPair[2];

    for (int i = 0; i < len; i += 2) {
        pair[0] = ciphertext[i];
        pair[1] = ciphertext[i + 1];
        decryptPair(keyTable, pair, decryptedPair);
        plaintext[i] = decryptedPair[0];
        plaintext[i + 1] = decryptedPair[1];
    }
    plaintext[len] = '\0';
}

int main() {
    char key[] = "CIPHER";
    char keyTable[SIZE][SIZE];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[sizeof(ciphertext)];

    generateKeyTable(key, keyTable);

    printf("Key Table:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyTable[i][j]);
        }
        printf("\n");
    }

    decryptMessage(keyTable, ciphertext, plaintext);

    printf("Decrypted message: %s\n", plaintext);

    return 0;
}
