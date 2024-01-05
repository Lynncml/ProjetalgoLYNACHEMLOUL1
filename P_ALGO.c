#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data);
void insertNode(struct Node **headRef, int data);
void displayList(struct Node *head);

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int buttonWidth = 130;
    const int buttonHeight = 40;

    InitWindow(screenWidth, screenHeight, "Linked List Visualization with Buttons");
    SetTargetFPS(60);

    struct Node *head = NULL;
Rectangle buttonAddRect = {(screenWidth - buttonWidth) / 2, 10, buttonWidth, buttonHeight};
    

    while (!WindowShouldClose()) {
        // Update

        // Check for button click to add a new element
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();

            // Add Element button
            if (CheckCollisionPointRec(mousePoint, buttonAddRect)) {
                // Add a random element to the list
                insertNode(&head, GetRandomValue(1, 100));
                printf("Node added\n");
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Display the linked list with arrows
        displayList(head);

        // Draw Add Element button
        DrawRectangleRec(buttonAddRect, BLUE);
        DrawText("Add Element", buttonAddRect.x + 10, buttonAddRect.y + 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// Function to create a new node with given data
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node with given data at the end of the linked list
void insertNode(struct Node **headRef, int data) {
    struct Node *newNode = createNode(data);

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct Node *current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to display a linked list with arrows
void displayList(struct Node *head) {
    struct Node *current = head;
    int xPos = 50;
    const int nodeSize = 40;
    const int arrowSize = 20;

    while (current != NULL) {
        // Draw rectangle for the node
        DrawRectangle(xPos, 200, nodeSize, nodeSize, PINK);
        DrawText(TextFormat("%d", current->data), xPos + 10, 210, 20, WHITE);

        // Draw arrow (if not the last node)
        if (current->next != NULL) {
            // Calculate arrow points
            Vector2 arrowStart = {xPos + nodeSize, 220};
            Vector2 arrowEnd = {xPos + nodeSize + arrowSize, 220};

            // Draw line
            DrawLine(arrowStart.x, arrowStart.y, arrowEnd.x, arrowEnd.y, BLACK);

            // Draw arrowhead
            DrawTriangle(
                (Vector2){arrowEnd.x - 10, arrowEnd.y - 5},
                (Vector2){arrowEnd.x, arrowEnd.y},
                (Vector2){arrowEnd.x - 10, arrowEnd.y + 5},
                BLACK
            );
        }

        xPos += (nodeSize + arrowSize);
        current = current->next;
    }
}
