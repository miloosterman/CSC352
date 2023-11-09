#include "parser.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int errSeen = 0;

int main(int argc, char **argv) {
    // Check for correct number of arguments and handle errors
    FILE* inSource = stdin;

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

    // Parse the input file
    // ...

    // Construct the dependency graph
    // ...

    // Perform a post-order traversal starting from the specified target
    // ...

    // Clean up resources
    // ...

    return 0;
}

