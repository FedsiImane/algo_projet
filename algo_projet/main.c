

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void createNode(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
        if (*head == NULL) {
                    *head = newNode;
                } else {
                    Node* current = *head;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newNode;
                }
    }
}
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
void freeList(Node* head) {
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void selectionSortAscending(Node** head) {
    Node *i, *j, *minNode;
    int frameCount = 0;

    for (i = *head; i != NULL; i = i->next) {
        minNode = i;

        for (j = i->next; j != NULL; j = j->next) {
            if (j->data < minNode->data) {
                minNode = j;
            }
        }

        int temp = i->data;
        i->data = minNode->data;
        minNode->data = temp;
    }
}

        
int main(void){
    Node* myList = NULL;
    int i , val , n;
    
    printf (" entrer n :");
    scanf ("%d",&n);
    for (i=0 ; i< n ; i++){
        printf (" entrer val :");
        scanf ("%d",&val);
        createNode(&myList, val);
    }
    printf("Original List: ");
    printList(myList);
    
    selectionSortAscending(&myList);
    
    freeList(myList);
    return 0;
}
