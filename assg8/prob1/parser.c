#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validName(char* str){
	if (strlen(str) > 64){
		return 0;
	}
	return 1;
}

FILE* openFile(int argc, char** argv){
	FILE* inStream = stdin;
	if (argc < 1){
		if (argc < 2){
			fprintf(stderr, "More than one argument\n");
			exit(1);
		}
		inStream = fopen(argv[1], "r");
		if (inStream == NULL) {
			perror(argv[1]);
			exit(1);
		}
	}

    return inStream;
}

void createGraph(FILE* inStream){
	char* line = NULL;
	char str[65];
	size_t sz = 0;
	char* ptr;
	char* colon;
	Node* target = NULL;

	while (getline(&line, &sz, inStream) > 0) {
		ptr = line;

		if (!(*ptr == '\t') && !(strchr(line, ':'))){
			fprintf(stderr, "Incorrect input\n");
			exit(1);
		}

		// If line starts with tab and target initialized, add command to target
		if (*ptr == '\t'){
			if (!target){
				fprintf(stderr, "Command given before target initialized\n");
				exit(1);
			}
			addCommand(target, ptr + 1);
			continue;
		}
		// Reset flag
		// If line contains colon, declare target
		if ((colon = strchr(line, ':'))){
			char* targetStart = line;
			char* targetEnd = colon;
            // Remove leading spaces
			while (isspace(*targetStart) && targetStart < colon){
				targetStart++;
			}
            // Remove trailing spaces
			while (isspace(*(targetEnd - 1)) && targetEnd > targetStart) {
				targetEnd--;
			}
			*targetEnd = '\0'; // Null-terminate the target string

			if (strchr(targetStart, ' ')) {
				fprintf(stderr, "Multiple targets are not allowed.\n");
				exit(1);
			}

            if (!validName(targetStart)){
                fprintf(stderr, "Target name too long\n");
                exit(1);
            }

			// Error if target has already been used
			if ((target = findNode(line)) && target->isTarget){
				fprintf(stderr, "%s was already a target\n", line);
				exit(1);
            // If in graph but not target, do not add, but set flags and vars
			} else if ((target = findNode(line))) {
				target->isTarget = 1;
				ptr = colon + 1;
            // If new target, add to graph, set flags and vars
			} else {
				target = addNode(ptr);
				target->isTarget = 1;
				ptr = colon + 1;
			}
		} 

		// For each dependency, add edge from target to dependency, creating dependency node if needed
		while (sscanf(ptr, "%64s", str) > 0) {
			// Check valid name
			if (!validName(str)) {
				perror("Invalid name\n");
				exit(1);
			}
			Node* depNode = findNode(str);
			// If dependency already exists add edge without creating new node 
			if (depNode != NULL) {
				addEdge(target->name, str);
				// Otherwise create new node and add edge
			} else {
				depNode = addNode(str);
				addEdge(target->name, depNode->name);
			}
			// Iterate through spaces
			while (isspace(*ptr)) {
				++ptr;
			}
			// Iterate to next line
			while (*ptr && !isspace(*ptr)) {
				++ptr;
			}
		}

	}
    if (line) {
        free(line);
    }
}

int main(int argc, char** argv) {
    FILE* inStream = openFile(argc, argv);
    createGraph(inStream);
    if (!head){
        fprintf(stderr, "No commands given\n");
        return 1;
    }
	traverse(head);

    return 0;
}
