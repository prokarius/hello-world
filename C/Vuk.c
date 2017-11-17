#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

int ff[250002], onion[250002], bfs[5000002], start=0, end=0;

void push(int n){
    bfs[end] = n;
    ++end;
}

int main(){
    int i, j, N, M, pos, cot, temp, curr;
    char forest[502][502];
    scanf ("%d %d", &N, &M);
    for (i=0; i<N; i++){scanf ("%s", forest[i]);}
    for (i=0; i<N; i++){
        for (j=0; j<M; j++){
            if (forest[i][j] == 'V') pos = i*500 + j;
            else if (forest[i][j] == 'J') cot = i*500 + j;
            else if (forest[i][j] == '+') {
                temp = i*500 + j;
                bfs[end] = temp;
                ff[temp] = 1;
                ++end;
            }
        }
    }

    // BFS for each tree. ff is now an array of min distance to a tree.
    while (start != end){
        temp = bfs[start];
        ++start;
        i = temp/500;
        j = temp%500;
        curr = ff[temp];
        if (j+1 != M){
            if (ff[temp+1] == 0) {
                ff[temp+1] = curr+1;
                push(temp+1);
            }
        }
        if (j-1 != -1){
            if (ff[temp-1] == 0) {
                ff[temp-1] = curr+1;
                push(temp-1);
            }
        }
        if (i-1 >= 0){
            if (ff[temp-500] == 0){
                ff[temp-500] = curr+1;
                push(temp-500);
            }
        }
        if (i+1 < N){
            if (ff[temp+500] == 0){
                ff[temp+500] = curr+1;
                push(temp+500);
            }
        }
    }

    // Floodfill to see if he can reach his house
    start = 0;
    end = 0;
    bfs[end] = pos;
    ++end;
    onion[pos] = ff[pos];
    while (start != end){
        temp = bfs[start];
        ++start;
        i = temp/500;
        j = temp%500;
        if (j+1 != M){
            if (forest[i][j+1] != '+'){
                if (onion[temp+1] == 0){
                    onion[temp+1] = MIN(onion[temp], ff[temp+1]);
                    push(temp+1);
                }
                else if (onion[temp] > onion[temp+1] && onion[temp] <= ff[temp+1]){
                    onion[temp+1] = onion[temp];
                    push(temp+1);
                }
            }
        }
        if (j-1 != -1){
            if (forest[i][j-1] != '+'){
                if (onion[temp-1] == 0){
                    onion[temp-1] = MIN(onion[temp], ff[temp-1]);
                    push(temp-1);
                }
                else if (onion[temp] > onion[temp-1] && onion[temp] <= ff[temp-1]){
                    onion[temp-1] = onion[temp];
                    push(temp-1);
                }
            }
        }
        if (i-1 >= 0){
            if (forest[i-1][j] != '+'){
                if (onion[temp-500] == 0){
                    onion[temp-500] = MIN(onion[temp], ff[temp-500]);
                    push(temp-500);
                }
                else if (onion[temp] > onion[temp-500] && onion[temp] <= ff[temp-500]){
                    onion[temp-500] = onion[temp];
                    push(temp-500);
                }
            }
        }
        if (i+1 < N){
            if (forest[i+1][j] != '+'){
                if (onion[temp+500] == 0){
                    onion[temp+500] = MIN(onion[temp], ff[temp+500]);
                    push(temp+500);
                }
                else if (onion[temp] > onion[temp+500] && onion[temp] <= ff[temp+500]){
                    onion[temp+500] = onion[temp];
                    push(temp+500);
                }
            }
        }
    }

    if (onion[cot]){
        printf("%d", onion[cot]-1);
    }
    else{
        printf("0");
    }
    return 0;
}
