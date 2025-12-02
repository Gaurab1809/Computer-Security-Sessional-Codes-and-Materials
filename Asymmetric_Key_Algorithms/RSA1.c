#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int e, int phi) {
    int d = 0, k = 1;
    while (1) {
        d = (1 + (k * phi)) / e;
        if (((d * e) % phi) == 1)
            return d;
        k++;
    }
}

int main() {
    int p = 13, q = 11;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e;
    for (e = 2; e < phi; e++)
        if (gcd(e, phi) == 1) break;

    int d = modInverse(e, phi);
    printf("P = %d, q = %d)\n", p, q);
    printf("Public Key  (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n\n", d, n);

    int msg;
    printf("Enter a message: ", n);
    scanf("%d", &msg);

    long long C = 1;
    for (int i = 0; i < e; i++)
        C = (C * msg) % n;

    long long M = 1;
    for (int i = 0; i < d; i++)
        M = (M * C) % n;

    printf("\nPlaintext  = %d\n", msg);
    printf("Ciphertext = %lld\n", C);
    printf("Decrypted  = %lld\n", M);

    return 0;
}
