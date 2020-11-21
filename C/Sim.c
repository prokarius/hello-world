#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    struct Node* next;
    struct Node* prev;
    char chr;
} Node;

Node* node(char c){
    Node* out = (Node*) malloc(sizeof(Node));
    out->chr = c;
    return out;
}

void print(Node* curr, Node* end){
    while (curr != end){
        printf("%c", curr->chr);
        curr = curr->next;
    }
    printf("\n");
}


// Inserts a new node after the current position
Node* insert(Node* curr, char c){
    Node* new = node(c);
    Node* next = curr->next;

    curr->next = new;
    next->prev = new;

    new->next = next;
    new->prev = curr;

    return new;
}

// Deletes the current node
Node* delete(Node* curr){
    Node* prev = curr->prev;
    Node* next = curr->next;

    prev->next = next;
    next->prev = prev;

    return prev;
}

void solve(){
    // Scan in input
    Node* start = node('$');
    Node* end = node('$');

    // Lord have mercy
    start->next = end;
    end->prev = start;
    Node* curr = start;

    // Process each letter independently
    char letter;
    scanf("%c", &letter);
    while(letter != '\n'){
        switch (letter){
            case ('<'):
                if (curr != start){
                    curr = delete(curr);
                }
                break;
            case ('['):
                curr = start;
                break;
            case (']'):
                curr = end->prev;
                break;
            default:
                curr = insert(curr, letter);
                break;
        }
        scanf("%c", &letter);
    }

    // Then we print it I guess...?
    print(start->next, end);
}

int main(){
    int testcases;
    scanf("%d ", &testcases); 

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}

