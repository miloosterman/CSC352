/* 
 * Author:Milo Osterman
 * File: changeBase.c
 * Purpose: This program is a base system converter
 * it reads in the base to be used, then a list white space seperated strings
 * that represent numbers in that base. For each, it converts them into base10
 * and prints the value.
 * */

#include <stdio.h>
#include <ctype.h>

// Takes a char and converts it into an integer
int convertToInt(char c){
	int res = 0;
	if (isalpha(c)){
		c = toupper(c);
		res = c - 55;
	} else {
		res = c - '0';
	}
	return res;
}

int main(){
	int base = 0;
	char input[7] = {0};
	
	if (scanf("%d", &base) != 1 || base > 36 || base == 1){
		fprintf(stderr, "The first value was invalid, must be an integer between 2-36\n");
		return 1;
	}

	while (scanf("%6s", input) != EOF){
		long unsigned int res = 0;
		int valid = 1;
		for (int i = 0; input[i] != '\0'; ++i){
			valid = 1;
			int converted = 0;
			if (isalnum(input[i])){
				converted = convertToInt(input[i]);
				if (converted > base){
					valid = 0;
					printf("An invalid %d-base number was entered\n", base);
					break;
				}
			res = base*res + (converted);
			
			} else {
				valid = 0;
				printf("Non alpha-numeric value entered.\n");
			}
		}
		if (valid){
			printf("%lu\n", res);
		}

	}

	return 0;
}

