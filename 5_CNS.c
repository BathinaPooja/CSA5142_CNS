#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

char affineEncrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        ch = toupper(ch); 
        return (char)(((a * (ch - 'A') + b) % ALPHABET_SIZE) + 'A');
    }
    return ch;
}

char affineDecrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        ch = toupper(ch); 
        int a_inv = 0;
        int flag = 0;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            flag = (a * i) % ALPHABET_SIZE;
            if (flag == 1) {
                a_inv = i;
                break;
            }
        }
        return (char)((a_inv * ((ch - 'A' - b + ALPHABET_SIZE) % ALPHABET_SIZE)) % ALPHABET_SIZE + 'A');
    }
    return ch;
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int a, b;

    // Get inputs
    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    while (gcd(a, ALPHABET_SIZE) != 1) {
        printf("Invalid value for a. It must be coprime with 26. Enter again: ");
        scanf("%d", &a);
    }

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("Ciphertext: %s\n", ciphertext);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = affineDecrypt(ciphertext[i], a, b);
    }
    decryptedtext[strlen(ciphertext)] = '\0';
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
