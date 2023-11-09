#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int errSeen = 0;

typedef struct Edge {
    struct Vertex* to;
    struct Edge* next;
    int dist;
} Edge;

typedef struct Vertex {
    char* name;
    Edge* edges;
    int marked;
    struct Vertex* next;
    int minDist;
} Vertex;

int validName(char* str){
    if (strlen(str) > 64){
        return 0;
    }
    while (*str){
        if (!isalpha(*str)){
            return 0;
        }
        ++str;
    }
    return 1;
}

Vertex* findVertex(char* name, Vertex* head){
    for (Vertex* vertex = head; vertex != NULL; vertex = vertex->next) {
        if (strcmp(vertex->name, name) == 0) {
            return vertex;
        }
    }
    return NULL;

}

int findEdge(Vertex* src, Vertex* dest){
    Edge* e;
    for (e = src->edges; e; e = e->next){
        if (e->to == dest){
            return 1;
        }
    }
    return 0;
}

Vertex* addVertex(char* name, Vertex* head){
    Vertex* newVertex = malloc(sizeof(Vertex));
    if (!newVertex){
        fprintf(stderr, "Memory allocation failure\n");
        exit(1);
    }
    newVertex->next = head;
    newVertex->name = strdup(name);
    if (newVertex->name == NULL) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(1);
    }
    newVertex->edges = NULL;
    return newVertex;
}

void addDirEdge(Vertex* src, Vertex* dest, int dist){
    Edge* newEdge = malloc(sizeof(Edge));
    if (!newEdge){
        fprintf(stderr, "Memory allocation failure\n");
        exit(1);
    }
    newEdge->to = dest;
    newEdge->dist = dist;
    newEdge->next = src->edges;
    src->edges = newEdge;
} 

void addUnEdge(char* n1, char* n2, int dist, Vertex *head){
    Vertex* v1 = findVertex(n1, head);
    Vertex* v2 = findVertex(n2, head);

    if (!v1 || !v2){
        fprintf(stderr, "Invalid vertex name\n");
        errSeen = 1;
        return;
    }

    if (findEdge(v1, v2) || findEdge(v2, v1)){
        fprintf(stderr, "Repeat Edge: %s %s %d\n", n1, n2, dist);
        errSeen = 1;
        return;
    }

    addDirEdge(v1, v2, dist);
    addDirEdge(v2, v1, dist);
}

int dijkstra(char* n1, char* n2, Vertex* head){
    Vertex* src = findVertex(n1, head);
    if (!src){
        fprintf(stderr, "Vertex not found\n");
        errSeen = 1;
        return -1;
    }

    Vertex* dest = findVertex(n2, head);
    if (!dest){
        fprintf(stderr, "Vertex not found\n");
        errSeen = 1;
        return -1;
    }

    for (Vertex* v = head; v; v = v->next){
        v->marked = 0;
        v->minDist = INT_MAX;
    }
    src->minDist = 0;

    while (1){
        Vertex* u = NULL;
        //u is unmarked vertex with smallest minDist val among all unmarked
        for (Vertex* v = head; v; v=v->next){
            if (!v->marked && (!u || v->minDist < u->minDist)){
                u = v;
            }
        }

        if (!u) {
            break;
        }
        //Mark vertex u
        u->marked = 1;

        //For each vertex v that is a neighbor of u:
        for (Edge* e = u->edges; e; e=e->next){
            Vertex* v = e->to;

            if (u->minDist + e->dist < v->minDist) {
                v->minDist = u->minDist + e->dist;
            }
        }
    }

    return dest->minDist;
}

Vertex* processInput(FILE *in) {
    char *line = NULL;
    size_t sz = 0;
    char arg1[66], arg2[66];
    int numArgs, arg3;
    Vertex* head = NULL;

    while (getline(&line, &sz, in) > 0) {
        numArgs = sscanf(line,"%65s%65s%d", arg1, arg2, &arg3);
        if (numArgs != 3){
            fprintf(stderr, "Incorrect number of arguments.\n");
            errSeen = 1;
            continue;
        }
        if (!validName(arg1)) {
            fprintf(stderr, "Invalid name%s\n", arg1);
            errSeen = 1;
            continue;
        }
        if (!validName(arg2)) {
            fprintf(stderr, "Invalid name%s\n", arg2);
            errSeen = 1;
            continue;
        }
        if (arg3 < 0) {
            fprintf(stderr, "Invalid Distance: %d\n", arg3);
            errSeen = 1;
            continue;
        }
        if (!findVertex(arg1, head)) {
            head = addVertex(arg1, head);
        }
        if (!findVertex(arg2, head)) {
            head = addVertex(arg2, head);
        }

        addUnEdge(arg1, arg2, arg3, head) ;
    }
    free(line);
    return head;
}

int processQueries(Vertex* head) {
    char* line = NULL;
    size_t sz = 0;
    char name1[66], name2[66];
    int numArgs;
    int dist;

    printf("Enter queries: \n");
    while (getline(&line, &sz, stdin) > 0){
        numArgs = sscanf(line, "%65s%65s", name1, name2);
        if (numArgs != 2){
            fprintf(stderr, "Incorrect number of arguments.\n");
            errSeen = 1;
            continue;
        }
        dist = dijkstra(name1, name2, head);
        if (dist > 0){
            printf("%d\n", dist);
        }
    }

    return 0;
}

void freeGraph(Vertex* head) {
    Vertex* currVertex = head;

    while (currVertex != NULL) {
        Edge* currentEdge = currVertex->edges;
        while (currentEdge != NULL) {
            Edge* nextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = nextEdge;
        }

        Vertex* nextVertex = currVertex->next;
        free(currVertex->name);
        free(currVertex);
        currVertex = nextVertex;
    }
}

int main(int argc, char *argv[]) {
    FILE* inSource = stdin;
    Vertex* head = NULL;

    if (argc > 1) {
        if (argc > 2) {
            fprintf(stderr, "Too many command-line arguments.\n");
            errSeen = 1;
        }
        inSource = fopen(argv[1], "r");
        if (inSource == NULL) {
            fprintf(stderr, "File could not be opened.");
            return 1;
        }
    }

    head = processInput(inSource);

    processQueries(head);

    freeGraph(head);
    fclose(inSource);

    return errSeen;
}
