#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

Node* head = NULL;

/*
 * Prints the name of a nodes commands and dependencies for testing purposes
 */

void printNodes(){
    Node* nptr;

    for (nptr = head; nptr!= NULL; nptr = nptr->next){
        printf("node: %s\n", nptr->name);
    }
}

void printGraph(){
    Node* nptr;
    Edge* eptr;
    Command* cptr;

    for (nptr = head; nptr != NULL; nptr = nptr->next){
        for (cptr = nptr->commands; cptr != NULL; cptr = cptr->next){
            printf("%s has command: %s\n", nptr->name, cptr->command);
        }
        for (eptr = nptr->edges; eptr != NULL; eptr = eptr->next){
            printf("%s edge to: %s\n", nptr->name, eptr->to->name);
        }
    }
}

/*
 * Finds a node in the graph from the name passed in as an argument
 */
Node* findNode(char* name){
    Node* temp = malloc(sizeof(Node));

    if (!temp){
        perror("Memory allocation failure\n");
        exit(1);
    }
    for (temp = head; temp; temp = temp->next){
        if (strcmp(name, temp->name) == 0){
            return temp;
        }
    }
    return NULL;
}

/*
 * Add a new node to the head of the linked list and set fields to null
 */
Node* addNode(char* name) {
    Node* newNode = malloc(sizeof(Node));

    if (!newNode){
        perror("Memory allocation failure\n");
        exit(1);
    }
    newNode->name = malloc(strlen(name)+1);
    if(newNode->name == NULL){
        perror("Memory allocation failure\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->edges = NULL;
    newNode->commands = NULL;
    newNode->visited = 0;
    newNode->isTarget = 0;
    newNode->next = head;
    head = newNode;
    return newNode;

}

/*
 * Add a new edge between two names provided as arguments. Return an error if the names of the nodes do not exist
 */
int addEdge(char* name1, char* name2) {
    Edge* newEdge;
    Node* node1;
    Node* node2;
    if (!(node1 = findNode(name1))){
        fprintf(stderr, "Node 1 not found\n");
        return 1;
    }
    if (!(node2 = findNode(name2))){
        fprintf(stderr, "Node 2 not found\n");
        return 1;
    }
    newEdge = malloc(sizeof(Edge));
    if (!newEdge){
        perror("Memory allocation failure\n");
        exit(1);
    }

    newEdge->to = node2;
    newEdge->next = NULL;

    if (node1->edges == NULL){
        node1->edges = newEdge;
    } else {
        Edge* curr = node1->edges;
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = newEdge;

    }

    return 0;
}

/*
 * Add the command string provided to the node provided as argument
 */
void addCommand(Node* node, char* command){
    Command* newCom = malloc(sizeof(Command));
    if (!newCom){
        perror("Memory allocation failure\n");
        exit(1);
    }
    newCom->next = node->commands;
    newCom->command = strdup(command);
    if(newCom->command == NULL){
        perror("Memory allocation failure\n");
        exit(1);
    }
    node->commands = newCom;
}

/*
 * Post order traversal of the graph, printing the dependency graph in proper ordering
 */
void traverse(Node* node){
    if (node->visited || node == NULL){
        return;
    }
    node->visited = 1;
    for(Edge* eptr = node->edges; eptr != NULL; eptr = eptr->next){
        traverse(eptr->to);
    }
    printf("%s\n", node->name);
    for(Command* cptr = node->commands; cptr; cptr = cptr->next){
        printf("  %s", cptr->command);
    }
}
