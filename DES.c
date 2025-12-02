#include <stdio.h>
#include <string.h>
int PC1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,
               10,2,59,51,43,35,27,19,11,3,60,52,44,36,
               63,55,47,39,31,23,15,7,62,54,46,38,30,22,
               14,6,61,53,45,37,29,21,13,5,28,20,12,4
              };
int PC2[48] = {14,17,11,24,1,5,3,28,15,6,21,10,
               23,19,12,4,26,8,16,7,27,20,13,2,
               41,52,31,37,47,55,30,40,51,45,33,48,
               44,49,39,56,34,53,46,42,50,36,29,32
              };
int SHIFTS[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int E_TABLE[48] = {32,1,2,3,4,5,4,5,6,7,8,9,
                   8,9,10,11,12,13,12,13,14,15,16,17,
                   16,17,18,19,20,21,20,21,22,23,24,25,
                   24,25,26,27,28,29,28,29,30,31,32,1
                  };
void permute(char *in, char *out, int *table, int n)
{
    for(int i=0; i<n; i++) out[i] = in[table[i]-1];
}
void leftShift28(char *in, char *out, int shift)
{
    for(int i=0; i<28; i++) out[i] = in[(i+shift)%28];
}
void xorBits(char *a, char *b, char *out, int n)
{
    for(int i=0; i<n; i++) out[i] = (a[i]==b[i])?'0':'1';
}
void expansionE(char *R, char *ER)
{
    for(int i=0; i<48; i++) ER[i] = R[E_TABLE[i]-1];
}
int main()
{
    char plaintext[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    char key[65]       = "0001001100110100010101110111100110011011101111001101111101000001";
    char PC1_out[57], C[4][29], D[4][29], CD[57], K[4][49];
    permute(key, PC1_out, PC1, 56);
    strncpy(C[0], PC1_out,28);
    C[0][28]='\0';
    strncpy(D[0], PC1_out+28,28);
    D[0][28]='\0';
    printf("C0=%s\nD0=%s\n\n",C[0],D[0]);
    for(int i=1; i<=3; i++)
    {
        leftShift28(C[i-1], C[i], SHIFTS[i-1]);
        leftShift28(D[i-1], D[i], SHIFTS[i-1]);
        strncpy(CD, C[i],28);
        strncpy(CD+28, D[i],28);
        CD[56]='\0';
        permute(CD, K[i], PC2,48);
        K[i][48]='\0';
        printf("Round %d key K%d = %s\n\n", i,i,K[i]);
    }
    char L[4][33], R[4][33];
    strncpy(L[0], plaintext,32);
    L[0][32]='\0';
    strncpy(R[0], plaintext+32,32);
    R[0][32]='\0';
    for(int i=1; i<=3; i++)
    {
        char ER[49], xorRes[49];
        expansionE(R[i-1], ER);
        ER[48]='\0';
        xorBits(ER,K[i],xorRes,48);
        xorRes[48]='\0';
        strncpy(L[i], R[i-1],32);
        L[i][32]='\0';
        for(int j=0; j<32; j++)
            R[i][j] = L[i-1][j]^xorRes[j]?'1':'0';
        R[i][32]='\0';
        printf("Round %d L%d=%s\n", i,i,L[i]);
        printf("Round %d R%d=%s\n\n", i,i,R[i]);
    }
    return 0;
}
