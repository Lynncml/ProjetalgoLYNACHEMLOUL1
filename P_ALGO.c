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
struct Node *searchNode(struct Node *head, int data);
void deleteNode(struct Node **headRef, int data);

// Déclaration des dimensions des boutons globalement
const int buttonWidth = 220;
const int buttonHeight = 40;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Linked List Visualization with Buttons");
    SetTargetFPS(60);

    struct Node *head = NULL;

    // Déclaration des rectangles pour les boutons
    Rectangle buttonAddRect = {(screenWidth - buttonWidth) / 2, 10, buttonWidth, buttonHeight};
    Rectangle buttonSearchRect = {(screenWidth - buttonWidth) / 2, 60, buttonWidth, buttonHeight};
    Rectangle buttonDeleteRect = {(screenWidth - buttonWidth) / 2, 110, buttonWidth, buttonHeight};

    while (!WindowShouldClose()) {
        // Update

        // Vérifiez le clic sur le bouton pour ajouter un nouvel élément
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();

            // Bouton "Ajouter Élément"
            if (CheckCollisionPointRec(mousePoint, buttonAddRect)) {
                // Ajouter un élément aléatoire à la liste
                insertNode(&head, GetRandomValue(1, 100));
                printf("Node added\n");
            }

            // Bouton "Rechercher Élément"
            else if (CheckCollisionPointRec(mousePoint, buttonSearchRect)) {
                // Valeur spécifique pour les tests (changez cette valeur au besoin)
                int valueToSearch = 1;
                struct Node *result = searchNode(head, valueToSearch);

                if (result != NULL) {
                    printf("Node found: %d\n", result->data);
                } else {
                    printf("Node not found\n");
                }
            }

            // Bouton "Supprimer Élément"
            else if (CheckCollisionPointRec(mousePoint, buttonDeleteRect)) {
                // Valeur spécifique pour les tests (changez cette valeur au besoin)
                int valueToDelete = 0;
                deleteNode(&head, valueToDelete);
                printf("Node deleted\n");
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Afficher la liste liée avec les flèches
        displayList(head);

        // Dessiner les boutons
        DrawRectangleRec(buttonAddRect, BLUE);
        DrawText("Ajouter Élément", buttonAddRect.x + 10, buttonAddRect.y + 10, 20, WHITE);

        DrawRectangleRec(buttonSearchRect, BLUE);
        DrawText("Rechercher Élément", buttonSearchRect.x + 10, buttonSearchRect.y + 10, 20, WHITE);

        DrawRectangleRec(buttonDeleteRect, BLUE);
        DrawText("Supprimer Élément", buttonDeleteRect.x + 10, buttonDeleteRect.y + 10, 20, WHITE);

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

// Function to search for a node with given data in the linked list
struct Node *searchNode(struct Node *head, int data) {
    struct Node *current = head;

    while (current != NULL && current->data != data) {
        current = current->next;
    }

    return current;
}

// Function to delete a node with given data from the linked list
void deleteNode(struct Node **headRef, int data) {
    struct Node *current = *headRef;
    struct Node *prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            *headRef = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
    }
}
