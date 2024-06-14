#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void calculateFrequency(char *text, int *frequency) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A']++;
        }
    }
}
void letterFrequencyAttack(char *ciphertext, int topN) {
    int frequency[26] = {0};
    char plaintext[1000];
    calculateFrequency(ciphertext, frequency);
    char mapping[26];
    int i, j;
    for (i = 0; i < 26; i++) {
        int maxFreq = -1, maxIndex = -1;
        for (j = 0; j < 26; j++) {
            if (frequency[j] > maxFreq) {
                maxFreq = frequency[j];
                maxIndex = j;
            }
        }
        frequency[maxIndex] = -1;
        mapping[maxIndex] = 'A' + i; 
    }
    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = mapping[ciphertext[i] - 'a'] + 32;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[i] = '\0';
    printf("Possible plaintexts in rough order of likelihood:\n");
    printf("%s\n", plaintext);
    if (topN > 1) {
        for (i = 1; i < topN; i++) {
            printf("%d. %s\n", i + 1, plaintext); 
        }
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}
