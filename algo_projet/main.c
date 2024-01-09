

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
        newNode->next = *head;
        *head = newNode;
    }
}

int main(){
    Node* myList = NULL;
    int i , val , n;
    
    printf (" entrer n :");
    scanf ("%d",&n);
    for (i=0 ; i< n ; i++){
        printf (" entrer val :");
        scanf ("%d",&val);
        createNode(&myList, val);
    }
   
}
