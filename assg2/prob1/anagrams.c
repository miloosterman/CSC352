/* 
 * Author:Milo Osterman
 * File: anagrams.c
 * Purpose: This program is used to check for anagrams from the input
 * the first value read in is compared to the following values read
 * if the value read is an anagram to the first value, print it
 * */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Take a char array and size value as parameters
// Sort array using bubble sort algorithm
void bubbleSort(char str[65], int size){
   for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
		str[j] = tolower(str[j]);
		str[j+1] = tolower(str[j+1]);
		if (str[j] > str[j + 1]) {
			char temp = str[j];
                	str[j] = str[j + 1];
                	str[j + 1] = temp;
	    }
	}
   }
}

// Take two char arrays as parameters
// Call bubble sort and use strcmp to see if they are anagrams
int isAnagram(char str1[], char str2[]){
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	if (len1 != len2){
		return 0;
	}

	bubbleSort(str1, len1);
	bubbleSort(str2, len2);

	return strcmp(str1, str2) == 0;
}

// Take char array as parameter
// Validate the chars in the string are alphabetical
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
	if (scanf("%64s", firstStr) != 1 || !checkValidStr(firstStr)){
		fprintf(stderr, "Input invalid.\n");
		return 1;
	} 	
	printf("%s\n", firstStr);
	while (scanf("%64s", str) != EOF){
		char unsorted[65] = {0};
		strcpy(unsorted, str);

		if (!checkValidStr(str)){
			fprintf(stderr, "The string cannot contain non-alphabetical characters\n");
		} else if (isAnagram(firstStr, str)){
			printf("%s\n", unsorted);
		}	
	}
	return 0;
}
