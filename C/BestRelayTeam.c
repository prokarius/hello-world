#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int fastSpeed;
    int slowSpeed;
    char name[25];
} Person;

Person person(int fastSpeed, int slowSpeed, char* name){
    Person out;
    out.fastSpeed = fastSpeed;
    out.slowSpeed = slowSpeed;
    strcpy(out.name, name);
    return out;
}

int cmpfunc(const void* a, const void* b){
    Person first = *(Person*)a;
    Person second = *(Person*)b;

    return (first.slowSpeed > second.slowSpeed)?(1):(-1);
}

Person runners[502];

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        char name[25];
        int fast1, fast2, slow1, slow2;

        scanf("%s %d.%d %d.%d", name, &fast1, &fast2, &slow1, &slow2);
        int fastSpeed = fast1*100 + fast2;
        int slowSpeed = slow1*100 + slow2;

        runners[i] = person(fastSpeed, slowSpeed, name);
    }

    // For each person, remove him and choose the best 3 other runners run qsort.
    // See if this gives a best timing
    int best = 1 << 30;
    Person person1, person2, person3, person4;
    Person tempPerson[505];
    for (int i = 0; i < n; ++i){
        // Copy all the people into a new array
        for (int j = 0; j < n; ++j){
            tempPerson[j] = runners[j];
        }

        tempPerson[i] = tempPerson[n-1];
        qsort(tempPerson, n-1, sizeof(Person), cmpfunc);

        // Calculate the speed of the team
        int curr = runners[i].fastSpeed;
        curr += tempPerson[0].slowSpeed;
        curr += tempPerson[1].slowSpeed;
        curr += tempPerson[2].slowSpeed;

        // Does the speed win?
        if (curr < best){
            best = curr;
            person1 = runners[i];
            person2 = tempPerson[0];
            person3 = tempPerson[1];
            person4 = tempPerson[2];
        }
    }

    // Print that shit
    printf("%d.%02d\n", best/100, best%100);
    printf("%s\n", person1.name);
    printf("%s\n", person2.name);
    printf("%s\n", person3.name);
    printf("%s\n", person4.name);

    return 0;
}
