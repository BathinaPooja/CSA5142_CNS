#include <stdio.h>
#include <stdlib.h>
#define MOD 26
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
    return -1;
}
int determinant(int a[2][2]) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}
void matrixInverse(int key[2][2], int invKey[2][2]) {
    int det = determinant(key);
    int detInv = multiplicativeInverse(det, MOD);
    if (detInv == -1) {
        printf("Determinant inverse does not exist. Key matrix is not invertible.\n");
        exit(1);
    }
    invKey[0][0] = mod26(key[1][1] * detInv);
    invKey[0][1] = mod26(-key[0][1] * detInv);
    invKey[1][0] = mod26(-key[1][0] * detInv);
    invKey[1][1] = mod26(key[0][0] * detInv);
}
void multiplyMatrices(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
            result[i][j] = mod26(result[i][j]);
        }
    }
}
void findKeyMatrix(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int plaintextInv[2][2];
    matrixInverse(plaintext, plaintextInv);
    multiplyMatrices(ciphertext, plaintextInv, key);
}

int main() {
    int plaintext[2][2] = { {12, 4}, {5, 19} };
    int ciphertext[2][2] = { {10, 22}, {15, 3} }; 
    int key[2][2];

    findKeyMatrix(plaintext, ciphertext, key);

    printf("Recovered Key Matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    return 0;
}
