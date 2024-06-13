#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt(char *plaintext, char *ciphertext, int *key, int length);
void decrypt(char *ciphertext, char *plaintext, int *key, int length);
void generate_random_key(int *key, int length);

int main() {
    // Example plaintext
    char plaintext[] = "HELLOVIGENERE";
    int length = strlen(plaintext);

    // Allocate memory for the ciphertext and key
    char *ciphertext = (char *)malloc(length + 1);
    char *decryptedtext = (char *)malloc(length + 1);
    int *key = (int *)malloc(length * sizeof(int));

    // Generate random key
    generate_random_key(key, length);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, key, length);
    ciphertext[length] = '\0';  // Null-terminate the string

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedtext, key, length);
    decryptedtext[length] = '\0';  // Null-terminate the string

    // Print results
    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decryptedtext);

    // Free allocated memory
    free(ciphertext);
    free(decryptedtext);
    free(key);

    return 0;
}

void encrypt(char *plaintext, char *ciphertext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        // Ensure plaintext is in uppercase and within alphabet range
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % ALPHABET_SIZE) + 'A';
        } else {
            ciphertext[i] = plaintext[i];  // Non-alphabetic characters are not encrypted
        }
    }
}

void decrypt(char *ciphertext, char *plaintext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        // Ensure ciphertext is in uppercase and within alphabet range
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabetic characters are not decrypted
        }
    }
}

void generate_random_key(int *key, int length) {
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}
