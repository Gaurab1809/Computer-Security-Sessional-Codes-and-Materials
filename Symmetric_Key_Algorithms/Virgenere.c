#include <stdio.h>
#include <string.h>
int letterToNum[26] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,
    20,21,22,23,24,25
};
char numToLetter[26] =
{
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};
int charToNum(char c)
{
    if(c >= 'A' && c <= 'Z')
        return letterToNum[c - 'A'];
    else
        return -1;
}
char numToChar(int n)
{
    if(n >= 0 && n < 26)
        return numToLetter[n];
    else
        return '?';
}
void vigenere(char plaintext[], char key[], char ciphertext[])
{
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    for(int i=0; i<textLen; i++)
    {
        int p = charToNum(plaintext[i]);
        int k = charToNum(key[i % keyLen]);
        int c = (p+k)%26;
        ciphertext[i] = numToChar(c);
    }
    ciphertext[textLen] = '\0';
}
int main()
{
    char plaintext[100], key[100], ciphertext[100];
    printf("Enter plaintext: ");
    scanf("%s", plaintext);
    printf("Enter key: ");
    scanf("%s", key);
    vigenere(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}
