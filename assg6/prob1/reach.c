#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    struct Node* link;
    struct Edge* next;
} Edge;

typedef struct Node {
    char name[65];
    Edge* edges;
    struct Node* next;
} Node;

void addVertex(Node** graph, char* name){
    Node* curr = *graph;

    while (curr){
        if (strcmp(curr->name, name) == 0){
            fprintf(stderr, "Vertex already exists in graph\n");
            return;
        }
        curr = curr->next;
    }

    Node* newVertex = (Node*)malloc(sizeof(Node));
    if (newVertex == NULL){
        fprintf(stderr, "Out of memory!\n");
        return;
    }

    strcpy(newVertex->name, name);
    newVertex->next = *graph;
    *graph = newVertex;
    printf("Vertex successfully added\n");

}

/*Add param for file name.*/
int main() {
    char* line = NULL;
    size_t len = 0;
    Node* graph = NULL;

    while (getline(&line, &len, stdin) != EOF) {
        char op;
        char arg1[65];
        char arg2[65];

        if (sscanf(line, "@%c %s %s", &op, arg1, arg2) != 0){
            switch (op) {
                case 'n':
                    addVertex(&graph, arg1);
                    break;
                case 'e':
                    /*Handle adding edge*/
                    break;
                case 'q':
                    /*Handle checking path*/
                    break;
                default:
                    fprintf(stderr, "Invalid operation\n");
            }

        }
    }


}
