
#include"raylib.h"
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
            DrawRectangle(posX, 300, 50, 50, GRAY);
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

Node* insertAtPosition(Node* head, int position, int valueToInsert) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        
        TraceLog(LOG_ERROR, "Erreur d'allocation de mémoire");
        return head;
    }

    newNode->data = valueToInsert;

    if (position == 0) {
        
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    int currentPosition = 0;

while (current != NULL && currentPosition < position - 1) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL) {
        
        free(newNode);
        return head;
    }

    
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

Node* searchValue(Node* head, int targetValue) {
    Node* current = head;

    while (current != NULL) {
        if (current->data == targetValue) {
            
            return current;
        }
        current = current->next;
    }


    return NULL;
}

Node* deleteElement(Node* head, int targetValue) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data == targetValue) {
            
            if (prev == NULL) {
                
                head = current->next;
            } else {
               
                prev->next = current->next;
            }

           
            free(current);
            return head;
        }

        prev = current;
        current = current->next;
    }

    return head;
}

void closeAndClean() {
    CloseWindow();
}

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib Selection Sort Animation");

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
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        drawListWithAnimation(myList, NULL, NULL, "", 0);
        
        DrawRectangle(10, 500, 170, 50, PINK);
        DrawText("Sort Ascending", 20, 510, 20, BLACK);
        DrawRectangle(200, 500, 180, 50, PINK);
        DrawText("Sort Descending", 210, 510, 20, BLACK);

        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePos, (Rectangle){10, 500, 150, 50})) {
                selectionSortAscending(&myList);
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){200, 500, 150, 50})) {
                selectionSortDescending(&myList);
                
            }
        }
if (CheckCollisionPointRec(mousePos, (Rectangle){10, 550, 100, 40})) {
    
    int position;
    printf("Enter position to insert: ");
    scanf("%d", &position);
    myList = insertAtPosition(myList, position, valueToInsert);


    int valueToInsert;
    printf("Enter value to insert: ");
    scanf("%d", &valueToInsert);
    myList = insertAtPosition(myList, position, valueToInsert);
}


while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    

   
    DrawRectangle(10, 550, 100, 40, GREEN);
    DrawText("Insert", 30, 560, 20, BLACK);

   
    DrawRectangle(120, 550, 100, 40, RED);
    DrawText("Delete", 140, 560, 20, WHITE);

   
    DrawRectangle(230, 550, 100, 40, BLUE);
    DrawText("Search", 250, 560, 20, WHITE);

    EndDrawing();

    
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mousePos, (Rectangle){10, 550, 100, 40})) {
            
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){120, 550, 100, 40})) {
         
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){230, 550, 100, 40})) {
            
        }
    }
}

        
        EndDrawing();
    }

    CloseWindow();
    freeList(myList);
    return 0;
