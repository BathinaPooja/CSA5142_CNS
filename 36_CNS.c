#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int gcd(int a, int b);
int mod_inverse(int a, int m);
void encrypt(char *plaintext, char *ciphertext, int a, int b);
void decrypt(char *ciphertext, char *plaintext, int a, int b);

int main() {
    
    char plaintext[] = "HELLOAFFINECIPHER";
    int length = strlen(plaintext);

   
    int a = 5; 
    int b = 8;

    if (gcd(a, ALPHABET_SIZE) != 1) {
        printf("Error: a is not coprime with 26. Choose a different value for a.\n");
        return 1;
    }

  
    char *ciphertext = (char *)malloc(length + 1);
    char *decryptedtext = (char *)malloc(length + 1);

   
    encrypt(plaintext, ciphertext, a, b);
    ciphertext[length] = '\0';  
 
    decrypt(ciphertext, decryptedtext, a, b);
    decryptedtext[length] = '\0';  
   
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decryptedtext);

    free(ciphertext);
    free(decryptedtext);

    return 0;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) {
            return x;
        }
    }
    return 1; 
}

void encrypt(char *plaintext, char *ciphertext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int p = toupper(plaintext[i]) - 'A';
            ciphertext[i] = ((a * p + b) % ALPHABET_SIZE) + 'A';
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
}

void decrypt(char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = mod_inverse(a, ALPHABET_SIZE);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int c = toupper(ciphertext[i]) - 'A';
            plaintext[i] = (a_inv * (c - b + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
}
