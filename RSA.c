#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int e, int phi) {
    int d;
    for (d = 1; d < phi; d++) {
        if (((d * e) % phi) == 1)
            return d;
    }
    return -1;
}
int main() {
    int p, q;
    printf("Enter the first Prime Number, p = ");
    scanf("%d", &p);
    printf("Enter the second Prime Number, q = ");
    scanf("%d", &q);
    printf("\n");
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }
    int d = modInverse(e, phi);
    printf("\n========== RSA KEY GENERATION ==========\n");
    printf("Step 1: Selected primes: p = %d, q = %d\n", p, q);
    printf("Step 2: Compute n = p * q = %d * %d = %d\n", p, q, n);
    printf("Step 3: Compute phi(n) = (p-1)*(q-1) = %d\n", phi);
    printf("Step 4: Select e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1\n");
    printf("Let, e = %d\n", e);
    printf("Step 5: Compute d such that (d * e) mod phi(n) = 1\n");
    printf("Calculated d = %d\n", d);
    printf("\n");
    printf("\n==========================================\n");
    printf("Public Key (e, n)  = (%d, %d)\n", e, n);
    printf("Private Key (d, n) = (%d, %d)\n", d, n);
    printf("\n========================================\n\n");
    int msg;
    printf("Enter a message (integer < %d) to encrypt: ", n);
    scanf("%d", &msg);
    long long int C = 1;
    for (int i = 0; i < e; i++)
        C = (C * msg) % n;
    long long int M = 1;
    for (int i = 0; i < d; i++)
        M = (M * C) % n;
    printf("\n========== RSA ENCRYPTION ==========\n");
    printf("Plain message (M) = %d\n", msg);
    printf("Ciphertext (C) = (M^e) mod n = (%d^%d) mod %d = %lld\n", msg, e, n, C);
    printf("====================================\n");
    printf("\n========== RSA DECRYPTION ==========\n");
    printf("Ciphertext (C) = %lld\n", C);
    printf("Decrypted message (M) = (C^d) mod n = (%lld^%d) mod %d = %lld\n", C, d, n, M);
    printf("====================================\n");
    return 0;
}
