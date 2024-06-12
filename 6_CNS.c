#include <stdio.h>
#include <string.h>
#include <ctype.h>
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
     
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

char affineDecrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        ch = toupper(ch); 
        int a_inv = modInverse(a, 26);
        return (char)((a_inv * ((ch - 'A' - b + 26) % 26)) % 26 + 'A');
    }
    return ch;
}

int main() {
    char ciphertext[100], decryptedtext[100];
    int a = 15, b;

    
    int E = 4, T = 19, B = 1, U = 20;
    
    b = (B - (15 * E % 26) + 26) % 26;
    printf("Calculated a: %d, b: %d\n", a, b);

    
    printf("Enter the ciphertext: ");
    scanf(" %[^\n]s", ciphertext);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = affineDecrypt(ciphertext[i], a, b);
    }
    decryptedtext[strlen(ciphertext)] = '\0';
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
