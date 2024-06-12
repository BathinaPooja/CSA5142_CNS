#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipherSequence(const char *keyword, char *cipher) {
    int used[26] = {0};
    int i, j = 0;
    for (i = 0; i < strlen(keyword); i++) {
        if (!used[toupper(keyword[i]) - 'A']) {
            cipher[j++] = toupper(keyword[i]);
            used[toupper(keyword[i]) - 'A'] = 1;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            cipher[j++] = 'A' + i;
        }
    }
    cipher[j] = '\0';
}
void encrypt(const char *plaintext, const char *cipher, char *encrypted) {
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            encrypted[i] = cipher[ch - 'A'];
        } else {
            encrypted[i] = plaintext[i];
        }
    }
    encrypted[strlen(plaintext)] = '\0';
}
void decrypt(const char *ciphertext, const char *cipher, char *decrypted) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            for (int j = 0; j < 26; j++) {
                if (cipher[j] == ch) {
                    decrypted[i] = 'A' + j;
                    break;
                }
            }
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[strlen(ciphertext)] = '\0';
}
int main() {
    const char *keyword = "CIPHER";
    char cipher[27];
    char plaintext[100];
    char encrypted[100];
    char decrypted[100];
    generateCipherSequence(keyword, cipher);
    printf("Cipher sequence: %s\n", cipher);
    printf("Enter a plaintext message: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    encrypt(plaintext, cipher, encrypted);
    printf("Encrypted message: %s\n", encrypted);
    decrypt(encrypted, cipher, decrypted);
    printf("Decrypted message: %s\n", decrypted);
    return 0;
}
