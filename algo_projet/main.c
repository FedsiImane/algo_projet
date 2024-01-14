
#include"raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
void drawList(Node* head, const char* label, int posX, int posY) {
    const int spacing = 60;
    Node* current = head;

    DrawText(label, posX, posY - 30, 20, BLACK);

    while (current != NULL) {
        DrawRectangle(posX, posY, 50, 50, BLUE);
        DrawText(TextFormat("%d", current->data), posX + 10, posY + 10, 20, WHITE);

        if (current->next != NULL) {
            DrawLine(posX + 50, posY + 25, posX + spacing, posY + 25, DARKGRAY);
            DrawTriangle((Vector2){posX + spacing, posY + 25}, (Vector2){posX + spacing - 10, posY + 20}, (Vector2){posX + spacing - 10, posY + 30}, DARKGRAY);
        }

        posX += spacing;
        current = current->next;
    }
}
void drawInputArea(char* buffer, int bufferIndex) {
    DrawRectangle(10, 10, 200, 50, LIGHTGRAY);
    DrawText("Enter Value:", 20, 20, 20, BLACK);
    DrawRectangle(220, 10, 100, 30, WHITE);
    DrawText(buffer, 230, 20, 20, BLACK);
}
int textToInt(const char* text) {
    int result;
    sscanf(text, "%d", &result);
    return result;
}
void handleInput(char* buffer, int* bufferIndex) {
    int key = GetKeyPressed();

    if (key != 0) {
       
        if ((key >= KEY_ZERO && key <= KEY_NINE) || key == KEY_BACKSPACE) {
            if ((*bufferIndex) < 15) {
                
                if (key == KEY_BACKSPACE && (*bufferIndex) > 0) {
                    buffer[--(*bufferIndex)] = '\0';
                } else {
                    
                    buffer[(*bufferIndex)++] = (char)key;
                    buffer[(*bufferIndex)] = '\0';
                }
            }
        }
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
         float yOffset = 1 * sin(frameCount * 0.2f);
            DrawRectangle(posX, 300+yOffset, 50, 50, Fade (GRAY,0.8));
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
if (i != minNode){
        int temp = i->data;
        i->data = minNode->data;
        minNode->data = temp;
        }
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
if (i != maxNode) {
        int temp = i->data;
        i->data = maxNode->data;
        maxNode->data = temp;
         }
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


int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib Selection Sort Animation");

    Node* myList = NULL;
    char buffer[16] = "";
    int bufferIndex = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        handleInput(buffer, &bufferIndex);

        drawInputArea(buffer, bufferIndex);
        if (bufferIndex > 0) {
            DrawRectangle(10, 70, 170, 50, PINK);
            DrawText("Add to List", 20, 80, 20, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){10, 70, 150, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int val = textToInt(buffer);
                createNode(&myList, val);
                buffer[0] = '\0';
                bufferIndex = 0;
            }
        }
     if (myList != NULL) {
            DrawRectangle(200, 70, 170, 50, PINK);
            DrawText("Sort Ascending", 210, 80, 20, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){200, 70, 150, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectionSortAscending(&myList);
            }

            DrawRectangle(380, 70, 170, 50, PINK);
            DrawText("Sort Descending", 390, 80, 20, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){380, 70, 150, 50}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectionSortDescending(&myList);
            }

            drawList(myList, "Current List:", 200, 150);
        }
         DrawRectangle(10, 550, 100, 40, GREEN);
        DrawText("Insert", 30, 560, 20, BLACK);

        DrawRectangle(120, 550, 100, 40, RED);
        DrawText("Delete", 140, 560, 20, WHITE);

        DrawRectangle(230, 550, 100, 40, BLUE);
        DrawText("Search", 250, 560, 20, WHITE);

        
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePos, (Rectangle){10, 550, 100, 40})) {
                int position;
                printf("Enter position to insert: ");
                scanf("%d", &position);

                int valueToInsert;
                printf("Enter value to insert: ");
                scanf("%d", &valueToInsert);
                myList = insertAtPosition(myList, position, valueToInsert);
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){120, 550, 100, 40})) {
                int targetValue;
                printf("Enter value to delete: ");
                scanf("%d", &targetValue);
                myList = deleteElement(myList, targetValue);
            } else if (CheckCollisionPointRec(mousePos, (Rectangle){230, 550, 100, 40})) {
                int targetValue;
                printf("Enter value to search: ");
                scanf("%d", &targetValue);
                Node* result = searchValue(myList, targetValue);
                if (result != NULL) {
                    printf("Value %d found in the list.\n", targetValue);
                } else {
                    printf("Value %d not found in the list.\n", targetValue);
                }
            }
        }
   
        EndDrawing();
    }

    CloseWindow();
    freeList(myList);
    return 0;
}
