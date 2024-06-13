#include <stdio.h>
#include <string.h>
int mod26(int a) {
    return (a % 26 + 26) % 26;
}
int multiplicativeInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}
void matrixInverse(int key[2][2], int invKey[2][2]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int detInv = multiplicativeInverse(det, 26);
    invKey[0][0] = mod26(key[1][1] * detInv);
    invKey[0][1] = mod26(-key[0][1] * detInv);
    invKey[1][0] = mod26(-key[1][0] * detInv);
    invKey[1][1] = mod26(key[0][0] * detInv);
}
void encrypt(char plaintext[], int key[2][2], char ciphertext[]) {
    int n = strlen(plaintext);
    for (int i = 0; i < n; i += 2) {
        int p1 = plaintext[i] - 'a';
        int p2 = plaintext[i + 1] - 'a';
        int c1 = mod26(key[0][0] * p1 + key[0][1] * p2);
        int c2 = mod26(key[1][0] * p1 + key[1][1] * p2);
        ciphertext[i] = c1 + 'a';
        ciphertext[i + 1] = c2 + 'a';
    }
    ciphertext[n] = '\0';
}
void decrypt(char ciphertext[], int invKey[2][2], char decrypted[]) {
    int n = strlen(ciphertext);
    for (int i = 0; i < n; i += 2) {
        int c1 = ciphertext[i] - 'a';
        int c2 = ciphertext[i + 1] - 'a';
        int p1 = mod26(invKey[0][0] * c1 + invKey[0][1] * c2);
        int p2 = mod26(invKey[1][0] * c1 + invKey[1][1] * c2);
        decrypted[i] = p1 + 'a';
        decrypted[i + 1] = p2 + 'a';
    }
    decrypted[n] = '\0';
}

int main() {
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";
    int key[2][2] = { {9, 4}, {5, 7} };
    int invKey[2][2];
    char ciphertext[100];
    char decrypted[100];
    matrixInverse(key, invKey);
    encrypt(message, key, ciphertext);
    printf("Encrypted Message: %s\n", ciphertext);
    decrypt(ciphertext, invKey, decrypted);
    printf("Decrypted Message: %s\n", decrypted);

    return 0;
}
