/* 
 * Author:Milo Osterman
 * File: anagrams.c
 * Purpose: This program identifies and prints anagrams from a set of strings
 * The first string read is used for comparison to the following strings to
 * find if they are anagrams of that first string. If it is, it is printed
 * to stdout
 * */

#include <stdio.h>
#include <ctype.h>

int compareLength(char strOne[], char strTwo[]){
	int firstLength = 0;
	int secondLength = 0;

	for (int i=0; strOne[i] != '\0'; i++){
		firstLength++;
	}

	for (int i=0; strTwo[i] != '\0'; i++){
		secondLength++;
	}

	return firstLength == secondLength;
}


int checkValidStr(char str[65]){
	for (int i=0; str[i] != '\0'; i++){
		if (!isalpha(str[i])){
			return 0;
		}
	}
	return 1;
}

int main(){
	char str[65] = {0};
	char firstStr[65] = {0};
	int anagram = 0;
	
	if (scanf("%64s", firstStr) != 1 || !checkValidStr(firstStr)){
		fprintf(stderr, "Input invalid.");
		return 1;
	} else{
		printf("%s\n", firstStr);
	}
	while (scanf("%64s", str) != EOF){
		if (!checkValidStr(str)){
			fprintf(stderr, "The string cannot contain non-alphabetical characters");
		}
		else if (compareLength(firstStr, str)){
			for (int i=0; firstStr[i] != '\0'; i++){
				int match = 0;
				for (int j=0; str[j] != '\0'; j++){
					if (tolower(firstStr[i]) == tolower(str[j])){
						match = 1;
						break;
					}
				}
				if (match == 0){
					anagram = 0;
					break;
				} else {
					anagram = 1;
				}

			}	
			if (anagram == 1){
				printf("%s\n", str);

			}
		}
	}
	return 0;
}
