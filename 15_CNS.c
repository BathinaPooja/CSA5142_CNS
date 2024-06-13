#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double englishLetterFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
double calculateScore(char *text) {
    int letterCounts[26] = {0};
    int totalLetters = 0;
    double score = 0.0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            letterCounts[text[i] - 'A']++;
            totalLetters++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            letterCounts[text[i] - 'a']++;
            totalLetters++;
        }
    }
    for (int i = 0; i < 26; i++) {
        double observedFreq = (double)letterCounts[i] / totalLetters * 100;
        score += (observedFreq - englishLetterFreq[i]) * (observedFreq - englishLetterFreq[i]);
    }
    return score;
}
void decrypt(char *ciphertext, char *plaintext, int key) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = (ciphertext[i] - 'A' - key + 26) % 26 + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = (ciphertext[i] - 'a' - key + 26) % 26 + 'a';
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[length] = '\0';
}
typedef struct {
    char text[1000];
    double score;
} DecryptionResult;

int compareResults(const void *a, const void *b) {
    double scoreA = ((DecryptionResult *)a)->score;
    double scoreB = ((DecryptionResult *)b)->score;
    return (scoreA > scoreB) - (scoreA < scoreB);
}
int main() {
    char ciphertext[1000];
    DecryptionResult results[26];
    int topN;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    for (int key = 0; key < 26; key++) {
        decrypt(ciphertext, results[key].text, key);
        results[key].score = calculateScore(results[key].text);
    }
    qsort(results, 26, sizeof(DecryptionResult), compareResults);
    printf("\nTop %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d. %s (Score: %.2f)\n", i + 1, results[i].text, results[i].score);
    }
    return 0;
}
