
/*
 * File: getPrime.c
 * Author: Milo Osterman
 * Purpose: This file reads in an integer value and finds the next prime number higher than 
 * provided value. Prints the prime value foune.
 * */
#include <stdio.h>

int isPrime(int num){
	for (int i=num-1; i>1; i--){
		if (num % i == 0){
			return 0;
		}
	}
	
	return 1;
}

int main(){
	int num;
	int status;
	status = scanf("%d", &num);
	if (num < 1){
		fprintf(stderr, "Value entered is non-positive\n");
		return 1;
	} else if (status == 0){
		fprintf(stderr, "Value entered is a non-integer\n");
		return 1;
	} else {
		while(isPrime(num) != 1){
			num += 1;			
		}

		printf("%d\n", num);

	return 0;

	}
}

