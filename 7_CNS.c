#include <stdio.h>
#include <string.h>
void decrypt(const char *ciphertext, const char *substitutionTable, char *plaintext) {
    int i, j;
    for (i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        for (j = 0; j < 94; j++) {
            if (substitutionTable[j] == ch) {
                plaintext[i] = '!' + j;
                break;
            }
        }
        if (j == 94) {
            plaintext[i] = ch;
        }
    }
    plaintext[i] = '\0'; 
}
int main() {
    const char *ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    char substitutionTable[94] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:',.<>?/`~";
    char plaintext[512];  
    decrypt(ciphertext, substitutionTable, plaintext);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}
