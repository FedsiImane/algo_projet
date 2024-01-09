

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

void drawListWithAnimation(Node* head, Node* node1, Node* node2, const char* swapDetails, int frameCount) {
    const int spacing = 60;
    int posX = 50;
    Node* current = head;

    while (current != NULL) {
        DrawRectangle(posX, 300, 50, 50, BLUE);
        DrawText(TextFormat("%d", current->data), posX + 10, 310, 20, WHITE);

        if (current->next != NULL) {
            DrawLine(posX + 50, 325, posX + spacing, 325, DARKGRAY);
            DrawTriangle((Vector2){posX + spacing, 325}, (Vector2){posX + spacing - 10, 320}, (Vector2){posX + spacing - 10, 330}, DARKGRAY);
        }

        if (current == node1 || current == node2) {
            DrawRectangle(posX, 300, 50, 50, RED);
            DrawText(swapDetails, 10, 400, 20, BLACK);
        }

        posX += spacing;
        current = current->next;
    }

    DrawText(TextFormat("Frame: %d", frameCount), 10, 430, 20, BLACK);
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
        
        char swapDetails[50];
        sprintf(swapDetails, "Swapped %d with %d", i->data, minNode->data);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Selection Sort (Ascending)", 10, 10, 20, BLACK);
        drawListWithAnimation(*head, i, minNode, swapDetails, frameCount++);
        EndDrawing();
        for (int delay = 0; delay < 1000000000; delay++);
    }
}
void selectionSortDescending(Node** head) {
    Node *i, *j, *maxNode;
    int frameCount = 0;

    for (i = *head; i != NULL; i = i->next) {
        maxNode = i;

        for (j = i->next; j != NULL; j = j->next) {
            if (j->data > maxNode->data) {
                maxNode = j;
            }
        }

        int temp = i->data;
        i->data = maxNode->data;
        maxNode->data = temp;
        
        char swapDetails[50];
        sprintf(swapDetails, "Swapped %d with %d", i->data, maxNode->data);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Selection Sort (Descending)", 10, 10, 20, BLACK);
        drawListWithAnimation(*head, i, maxNode, swapDetails, frameCount++);
        EndDrawing();
        for (int delay = 0; delay < 1000000000; delay++);
    }
}

        
int main(void){
    Node* myList = NULL;
    int i , val , n , choice ;
    
    printf (" entrer n :");
    scanf ("%d",&n);
    for (i=0 ; i< n ; i++){
        printf (" entrer val :");
        scanf ("%d",&val);
        createNode(&myList, val);
    }
    printf("Original List: ");
    printList(myList);
    
    printf (" entrer choice entre 1 et 2 :");
    scanf ("%d",&choice);
    if (choice == 1){
        selectionSortAscending(&myList);
        printList(myList);
    }else if (choice == 2){
        selectionSortDescending(&myList);
        printList(myList);
    }else{
        printf(" there is no choice like this ");
    }
    freeList(myList);
    return 0;
    
}
