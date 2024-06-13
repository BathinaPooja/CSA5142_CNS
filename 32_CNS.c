#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define MESSAGE "This is a test message"

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

void print_hex(const char *label, const unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
void generate_dsa_signatures() {
    DSA *dsa = DSA_new();
    if (dsa == NULL) handle_errors();

    if (!DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL))
        handle_errors();
    if (!DSA_generate_key(dsa)) handle_errors();

    unsigned char *sig1 = NULL;
    unsigned int sig1_len;
    unsigned char *sig2 = NULL;
    unsigned int sig2_len;

    if (!DSA_sign(0, (unsigned char *)MESSAGE, strlen(MESSAGE), sig1, &sig1_len, dsa))
        handle_errors();
    if (!DSA_sign(0, (unsigned char *)MESSAGE, strlen(MESSAGE), sig2, &sig2_len, dsa))
        handle_errors();

    print_hex("DSA Signature 1", sig1, sig1_len);
    print_hex("DSA Signature 2", sig2, sig2_len);

    DSA_free(dsa);
    OPENSSL_free(sig1);
    OPENSSL_free(sig2);
}
void generate_rsa_signatures() {
    RSA *rsa = RSA_new();
    BIGNUM *bn = BN_new();
    if (!BN_set_word(bn, RSA_F4)) handle_errors();
    if (!RSA_generate_key_ex(rsa, 2048, bn, NULL)) handle_errors();

    unsigned char sig1[256];
    unsigned int sig1_len;
    unsigned char sig2[256];
    unsigned int sig2_len;

    if (!RSA_sign(NID_sha256, (unsigned char *)MESSAGE, strlen(MESSAGE), sig1, &sig1_len, rsa))
        handle_errors();
    if (!RSA_sign(NID_sha256, (unsigned char *)MESSAGE, strlen(MESSAGE), sig2, &sig2_len, rsa))
        handle_errors();

    print_hex("RSA Signature 1", sig1, sig1_len);
    print_hex("RSA Signature 2", sig2, sig2_len);

    RSA_free(rsa);
    BN_free(bn);
}

int main() {
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    printf("Generating DSA Signatures...\n");
    generate_dsa_signatures();

    printf("\nGenerating RSA Signatures...\n");
    generate_rsa_signatures();

    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
