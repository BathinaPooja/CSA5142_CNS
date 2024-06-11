#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt(char* plaintext, char* ciphertext, char* key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = key[plaintext[i] - 'a'];
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = key[plaintext[i] - 'A'] - 'a' + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char key[ALPHABET_SIZE + 1] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove the newline character if present
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len-1] == '\n') {
        plaintext[len-1] = '\0';
    }

    encrypt(plaintext, ciphertext, key);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
