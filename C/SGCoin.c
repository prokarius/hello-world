#include<stdio.h>
#include<string.h>

long long hash(long long previousHash, char* transaction){
    long long v = previousHash;
    for (int i = 0; i < strlen(transaction); i++) {
        v = (v * 31 + transaction[i]) % 1000000007;
    }
    return (v * 7) % 1000000007;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    char* strA = "notice-me-steven-halim-senpai";
    char* strB = "doki-doki-waku-waku";

    long long hash1 = hash(n, strA); 
    int out1 = 1000000000 - hash1; // Pray for cheese
    if (out1 < 0) out1 += 500000007;

    long long hash2 = hash((hash1 + out1), strB); 
    int out2 = 1000000000 - hash2; // Pray for cheese
    if (out2 < 0) out2 += 500000007;

    printf("%s %d\n%s %d\n", strA, out1, strB, out2);

    return 0;
}
