#include <stdio.h>
#define MIN(x,y) (x<y)?(x):(y)
#define MAX(x,y) (x>y)?(x):(y)

// The main loop for each test case
void cod (){
    int memsize, codelen, inputlen;
    char code[4100], input[4100];
    int memory[100002], sp=0, pc=0;
    int bracket[2100], stack[2100];
    int i=0, counter=0;
    scanf ("%d %d %d ", &memsize, &codelen, &inputlen);
    scanf("%s", code);
    scanf("%s", input);

    // Cleans the data arrays
    while (i<memsize){
        memory[i] = 0;
        ++i;
    }

    i=0;
    while (i<codelen){
        if (code[i] == '['){
            stack[counter] = i;
            ++counter;
        }
        else if (code[i] == ']'){
            --counter;
            bracket[stack[counter]] = i;
            bracket[i] = stack[counter];
        }
        ++i;
    }

    // Simulate the shit
    i = 0;
    counter = 0;
    while (counter < 50000000){
        switch(code[pc]){
            case '+':
                memory[sp] = (memory[sp] + 1) % 256;
                break;
            case '-':
                memory[sp] = (memory[sp] + 255) % 256;
                break;
            case '<':
                sp = (sp + 1) % memsize;
                break;
            case '>':
                sp = (sp + memsize - 1) % memsize;
                break;
            case '[':
                if (memory[sp] == 0) pc = bracket[pc];
                break;
            case ']':
                if (memory[sp] != 0) pc = bracket[pc];
                break;
            case '.':
                break;
            case ',':
                if (i < inputlen){
                    memory[sp] = (int) input[i];
                    ++i;
                }
                else memory[sp] = 255;
                break;
        }
        ++counter;
        ++pc;
        if (pc > codelen) break;
    }

    // If it terminates within 50M steps, pc > code.
    if (pc > codelen){
        printf("Terminates\n");
        return;
    }

    // If not, it is looping. We simulate 50M more steps to tell where it loops
    int loopstart = 9999, loopend = -1;
    while (counter < 100000000){
        switch(code[pc]){
            case '+':
                memory[sp] = (memory[sp] + 1) % 256;
                break;
            case '-':
                memory[sp] = (memory[sp] + 255) % 256;
                break;
            case '<':
                sp = (sp + 1) % memsize;
                break;
            case '>':
                sp = (sp + memsize - 1) % memsize;
                break;
            case '[':
                if (memory[sp] == 0) pc = bracket[pc];
                break;
            case ']':
                // Looping! Where it loops will be the outer most bracket
                if (memory[sp] != 0){
                    loopend = MAX(pc, loopend);
                    pc = bracket[pc];
                    loopstart = MIN(pc, loopstart);
                }
                break;
            case '.':
                break;
            case ',':
                if (i < inputlen){
                    memory[sp] = (int) input[i];
                    ++i;
                }
                else memory[sp] = 255;
                break;
        }
        ++counter;
        ++pc;
    }
    printf ("Loops %d %d\n", loopstart, loopend);
    return;
}

int main(){
    int n;
    scanf ("%d", &n);
    while (n){
    cod ();
    --n;
    }
    return 0;
}
