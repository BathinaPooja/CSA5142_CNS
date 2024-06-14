
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 3
void encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext);
void matrixMultiply(int key[MATRIX_SIZE][MATRIX_SIZE], int *vector, int *result);
void knownPlaintextAttack(int plaintextMatrix[MATRIX_SIZE][MATRIX_SIZE], int ciphertextMatrix[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]);
void invertMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]);
int modInverse(int a, int m);
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]);
void adjugate(int matrix[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]);
void encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int vector[MATRIX_SIZE];
    int result[MATRIX_SIZE];
    int i, j, k = 0;

    while (plaintext[k] != '\0') {
        for (i = 0; i < MATRIX_SIZE; i++) {
            vector[i] = plaintext[k++] - 'A';
        }

        matrixMultiply(key, vector, result);

        for (i = 0; i < MATRIX_SIZE; i++) {
            ciphertext[k - MATRIX_SIZE + i] = (result[i] % 26) + 'A';
        }
    }
    ciphertext[k] = '\0';
}
void matrixMultiply(int key[MATRIX_SIZE][MATRIX_SIZE], int *vector, int *result) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            result[i] += key[i][j] * vector[j];
        }
    }
}
void knownPlaintextAttack(int plaintextMatrix[MATRIX_SIZE][MATRIX_SIZE], int ciphertextMatrix[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    invertMatrix(plaintextMatrix, inverse);

    matrixMultiply(inverse, (int *)ciphertextMatrix, (int *)key);
}
void invertMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int adj[MATRIX_SIZE][MATRIX_SIZE];
    adjugate(matrix, adj);

    int invDet = modInverse(det, 26);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] = (adj[i][j] * invDet) % 26;
            if (inverse[i][j] < 0) {
                inverse[i][j] += 26;
            }
        }
    }
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}
void adjugate(int matrix[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]) {
    adj[0][0] =  matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adj[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    adj[0][2] =  matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    adj[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    adj[1][1] =  matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adj[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
    adj[2][0] =  matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adj[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
    adj[2][2] =  matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    char plaintext[] = "ACT";
    char ciphertext[100];

    printf("Plaintext: %s\n", plaintext);

    encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    int plaintextMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {0, 2, 19},
        {0, 2, 19},
        {0, 2, 19}
    };
    int ciphertextMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {8, 5, 10},
        {8, 5, 10},
        {8, 5, 10}
    };

    int recoveredKey[MATRIX_SIZE][MATRIX_SIZE];
    knownPlaintextAttack(plaintextMatrix, ciphertextMatrix, recoveredKey);

    printf("Recovered key matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", recoveredKey[i][j]);
        }
        printf("\n");
    }

    return 0;
}
