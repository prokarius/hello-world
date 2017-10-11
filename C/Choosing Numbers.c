#include<stdio.h>
#define MAX(x,y) x>y ? x:y

//sqrt 2 billion < 44800
//We generated 4655 primes

int plist [4700], somelist[44800] = {0};

// Standard Prime Generator. Copy this shit.
void setting() {
    int g=-1, i ,j;
    somelist [0] = somelist[1] = 1;
    for (i=0; i<44800; ++i){
        if (somelist[i] != 0){
            continue;
        }
        plist[++g] = i;
        for (j=i; j<44800; j+=i){
            somelist[j] = 1;
        }
    }
}


int main(){
    setting();
    long long i, n, j, k, array[1005], array2[1005]={0};
    while (scanf("%lld", &n) != EOF){
        int dead[1005] = {0};
        long long output=0;
        i=0;
        
        // Scan this shit
        while (i < n){
            scanf("%lld", &array[i]);
            array2[i] = array[i];
            ++i;
        }

        //For all numbers cept the last dude
        for (i=0; i<n-1; ++i){ 

            // If it's dead, leave it
            if (array[i] == 1) continue;

            // Else, go through the prime list and find out its prime factors
            for (j=0; j<4653; ++j){

                // Oh, but if it's dead, leave it
                if (array[i] == 1) break;

                // If it is killed by the prime, let it be killed
                if (array[i]%plist[j] != 0) continue;
                while (array[i] % plist[j] == 0){
                    array[i] /= plist[j];
                }

                // Every other number that it can kill shall suicide together.
                for (k=i+1; k<n; ++k){
                    while (array[k] % plist[j] == 0){
                        array[k] /= plist[j];
                        dead[k] = 1;
                        dead[i] = 1;
                    }
                }
            }

            // If it's not dead, it is prime. Try to suicide everyone with it.
            if (array[i] != 1){
                for (k=i+1; k<n; ++k){
                    while (array[k] % array[i] == 0){
                        array[k] /= array[i];
                        dead[k] = 1;
                        dead[i] = 1;
                    }
                }
            }
        }
        // For the numbers that are still alive, find the max of them. Print
        for (i=0; i<n; ++i){
            if (dead[i] == 0) output = MAX (output, array2[i]);
        }
        printf ("%lld\n", output);
    }
    return 0;
}
