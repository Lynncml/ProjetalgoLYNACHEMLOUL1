#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data);
void insertNode(struct Node **headRef, int data);
void displayList(struct Node *head, int searchValue);
struct Node *searchNode(struct Node *head, int data);
void deleteNode(struct Node **headRef, int data);
void bubbleSort(struct Node *head);

// Déclaration des dimensions des boutons globalement
const int buttonWidth = 220;
const int buttonHeight = 40;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Linked List Visualization with Buttons");
    SetTargetFPS(60);

    struct Node *head = NULL;

    // Valeur recherchée
    int searchValue = -1;

    // Déclaration des rectangles pour les boutons
    Rectangle buttonAddRect = {(screenWidth - buttonWidth) / 50, 10, buttonWidth, buttonHeight};
    Rectangle buttonSearchRect = {(screenWidth - buttonWidth) / 50, 60, buttonWidth, buttonHeight};
    Rectangle buttonDeleteRect = {(screenWidth - buttonWidth) / 50, 110, buttonWidth, buttonHeight};
    Rectangle buttonSortRect = {(screenWidth - buttonWidth) / 50, 160, buttonWidth, buttonHeight};

    while (!WindowShouldClose()) {
        // Update

        // Vérifiez le clic sur le bouton pour ajouter un nouvel élément
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();

            // Bouton "Ajouter Élément"
            if (CheckCollisionPointRec(mousePoint, buttonAddRect)) {
                // Ajouter un élément aléatoire à la liste
                insertNode(&head, GetRandomValue(1, 10));
                printf("Node added\n");
            }

            // Bouton "Rechercher Élément"
            else if (CheckCollisionPointRec(mousePoint, buttonSearchRect)) {
                // Valeur spécifique pour les tests (changez cette valeur au besoin)
                int valueToSearch = 3;
                searchValue = valueToSearch;

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
                int valueToDelete = 3;
                deleteNode(&head, valueToDelete);
                printf("Node deleted\n");
            }

            // Bouton "Trier Liste"
            else if (CheckCollisionPointRec(mousePoint, buttonSortRect)) {
                // Trier la liste avec le tri à bulles
                bubbleSort(head);
                printf("List sorted\n");
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Afficher la liste liée avec les flèches et la valeur recherchée
        displayList(head, searchValue);

        // Dessiner les boutons
        DrawRectangleRec(buttonAddRect, PURPLE);
        DrawText("Ajouter Élément", buttonAddRect.x + 10, buttonAddRect.y + 10, 20, WHITE);

        DrawRectangleRec(buttonSearchRect, LIGHTGRAY);
        DrawText("Rechercher Élément", buttonSearchRect.x + 10, buttonSearchRect.y + 10, 20, WHITE);

        DrawRectangleRec(buttonDeleteRect, ORANGE);
        DrawText("Supprimer Élément", buttonDeleteRect.x + 10, buttonDeleteRect.y + 10, 20, WHITE);

        DrawRectangleRec(buttonSortRect, YELLOW);
        DrawText("Trier Liste", buttonSortRect.x + 10, buttonSortRect.y + 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// Fonction pour créer un nouveau nœud avec des données spécifiées
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour insérer un nœud avec des données spécifiées à la fin de la liste liée
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

// Fonction pour afficher une liste liée avec des flèches et la valeur recherchée
void displayList(struct Node *head, int searchValue) {
    struct Node *current = head;
    int xPos = 50;
    const int nodeSize = 40;
    const int arrowSize = 20;

    while (current != NULL) {
        // Dessiner un rectangle pour le nœud
        DrawRectangle(xPos, 200, nodeSize, nodeSize, PINK);
        DrawText(TextFormat("%d", current->data), xPos + 10, 210, 20, WHITE);

        // Dessiner une flèche (si ce n'est pas le dernier nœud)
        if (current->next != NULL) {
            // Calculer les points de la flèche
            Vector2 arrowStart = {xPos + nodeSize, 220};
            Vector2 arrowEnd = {xPos + nodeSize + arrowSize, 220};

            // Dessiner une ligne
            DrawLine(arrowStart.x, arrowStart.y, arrowEnd.x, arrowEnd.y, BLACK);

            // Dessiner la pointe de la flèche
            DrawTriangle(
                (Vector2){arrowEnd.x - 10, arrowEnd.y - 5},
                (Vector2){arrowEnd.x, arrowEnd.y},
                (Vector2){arrowEnd.x - 10, arrowEnd.y + 5},
                BLACK
            );
        }

        // Mettre en surbrillance la valeur recherchée
        if (current->data == searchValue) {
            DrawRectangleLines(xPos - 2, 200 - 2, nodeSize + 4, nodeSize + 4, BLACK);
        }

        xPos += (nodeSize + arrowSize);
        current = current->next;
    }
}

// Fonction pour rechercher un nœud avec des données spécifiées dans la liste liée
struct Node *searchNode(struct Node *head, int data) {
    struct Node *current = head;

    while (current != NULL && current->data != data) {
        current = current->next;
    }

    return current;
}

// Fonction pour supprimer un nœud avec des données spécifiées de la liste liée
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

// Fonction pour trier la liste liée avec le tri à bulles
void bubbleSort(struct Node *head) {
    if (head == NULL)
        return;

    int swapped;
    do {
        swapped = 0;
        struct Node *ptr = head;

        while (ptr->next != NULL) {
            if (ptr->data > ptr->next->data) {
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }

            ptr = ptr->next;
        }
    } while (swapped);
}
