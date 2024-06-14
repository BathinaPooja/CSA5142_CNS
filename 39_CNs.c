#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26
double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 
    1.974, 0.074
};
void decryptWithKey(char *ciphertext, char *plaintext, int key);
double calculateChiSquared(char *text);
void sortResults(double *scores, char texts[][100], int size);
void getTopNResults(double *scores, char texts[][100], int size, int n);

int main() {
    char ciphertext[100];
    int topN;

    printf("Enter the ciphertext: ");
    scanf("%s", ciphertext);

    printf("Enter the number of top results to display: ");
    scanf("%d", &topN);

    char possiblePlaintexts[ALPHABET_SIZE][100];
    double scores[ALPHABET_SIZE];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decryptWithKey(ciphertext, possiblePlaintexts[key], key);
        scores[key] = calculateChiSquared(possiblePlaintexts[key]);
    }
    sortResults(scores, possiblePlaintexts, ALPHABET_SIZE);
    getTopNResults(scores, possiblePlaintexts, ALPHABET_SIZE, topN);

    return 0;
}
void decryptWithKey(char *ciphertext, char *plaintext, int key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
    }
    plaintext[i] = '\0';
}
double calculateChiSquared(char *text) {
    int letterCounts[ALPHABET_SIZE] = {0};
    int textLength = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            letterCounts[text[i] - 'A']++;
            textLength++;
        }
    }

    double chiSquared = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double observed = letterCounts[i];
        double expected = textLength * englishFrequencies[i] / 100.0;
        chiSquared += ((observed - expected) * (observed - expected)) / expected;
    }

    return chiSquared;
}
void sortResults(double *scores, char texts[][100], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (scores[i] > scores[j]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                char tempText[100];
                strcpy(tempText, texts[i]);
                strcpy(texts[i], texts[j]);
                strcpy(texts[j], tempText);
            }
        }
    }
}

void getTopNResults(double *scores, char texts[][100], int size, int n) {
    printf("\nTop %d possible plaintexts:\n", n);
    for (int i = 0; i < n && i < size; i++) {
        printf("Plaintext: %s, Chi-Squared Score: %f\n", texts[i], scores[i]);
    }
}
