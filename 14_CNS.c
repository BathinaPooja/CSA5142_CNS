#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void generateKey(int key[], int length) {
    srand(time(0));
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}
void encrypt(char plaintext[], char ciphertext[], int key[]) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}
void decrypt(char ciphertext[], char plaintext[], int key[]) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decryptedText[100];
    int key[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    int length = strlen(plaintext);
    generateKey(key, length);
    encrypt(plaintext, ciphertext, key);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, decryptedText, key);
    printf("Decrypted text: %s\n", decryptedText);
    printf("Key stream: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    return 0;
}
