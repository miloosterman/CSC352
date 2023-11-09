#ifndef GRAPH_H
#define GRAPH_H

typedef struct Command {
    char* command;
    struct Command* next;
} Command;

typedef struct Edge {
    struct Node* to;
    struct Edge* next;
} Edge;

typedef struct Node {
    char* name;
    Edge* edges;
    Command* commands;
    int visited;
    int isTarget;
    struct Node* next;
} Node;

extern Node* head;

Node* findNode(char* name);
void printNodes();
void printGraph();
Node* addNode(char* name);
int addEdge(char* node1, char* node2);
void addCommand(Node* node, char* command);
void traverse(Node* node);


#endif // GRAPH_H

