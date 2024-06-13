#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int flag[26] = {0};
    int i, j, k = 0;
    int key_len = strlen(key);
    for (i = 0; i < key_len; i++) {
        key[i] = toupper(key[i]);
        if (key[i] == 'J') key[i] = 'I';
    }
    for (i = 0; i < key_len; i++) {
        if (!flag[key[i] - 'A']) {
            matrix[k / SIZE][k % SIZE] = key[i];
            flag[key[i] - 'A'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i == 'J' - 'A') continue; 
        if (!flag[i]) {
            matrix[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void printMatrix(char matrix[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void processText(char text[], char processedText[]) {
    int i, j = 0, len = strlen(text);

    for (i = 0; i < len; i++) {
        if (text[i] == 'J') text[i] = 'I';
        if (isalpha(text[i])) {
            processedText[j++] = toupper(text[i]);
        }
    }
    processedText[j] = '\0';
    len = strlen(processedText);
    for (i = 0; i < len; i += 2) {
        if (processedText[i] == processedText[i + 1]) {
            for (j = len; j > i; j--) {
                processedText[j] = processedText[j - 1];
            }
            processedText[i + 1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        processedText[len] = 'X';
        processedText[len + 1] = '\0';
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char matrix[SIZE][SIZE], char a, char b, char *c, char *d) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) {
        *c = matrix[row1][(col1 + 1) % SIZE];
        *d = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *c = matrix[(row1 + 1) % SIZE][col1];
        *d = matrix[(row2 + 1) % SIZE][col2];
    } else {
        *c = matrix[row1][col2];
        *d = matrix[row2][col1];
    }
}

void encrypt(char plaintext[], char ciphertext[], char matrix[SIZE][SIZE]) {
    int i, len = strlen(plaintext);

    for (i = 0; i < len; i += 2) {
        encryptPair(matrix, plaintext[i], plaintext[i + 1], &ciphertext[i], &ciphertext[i + 1]);
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[SIZE * SIZE], plaintext[100], processedText[100], ciphertext[100];
    char matrix[SIZE][SIZE];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove newline character

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character

    createMatrix(key, matrix);

    printf("5x5 Matrix:\n");
    printMatrix(matrix);

    processText(plaintext, processedText);
    printf("Processed Text: %s\n", processedText);

    encrypt(processedText, ciphertext, matrix);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
