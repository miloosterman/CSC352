/* 
 * Author:Milo Osterman
 * File: getPrime.c
 * Purpose: This file reads in a number of integer values and tests each one for whether it
 * is a factorial. For each value, prints the value and its factorial representation
 * if factorial, prints not factorial otherwise.
 * */

#include <stdio.h>

int main(){
	int num;
	int status;
	while(status != -1){
		status = scanf("%d", &num);
		if (status == 0){
			fprintf(stderr,"Error: input is not a number\n");
			return 1;
		} else if (num < 1) {
			fprintf(stderr, "Error: input value %d is not positive\n", num);
		} else {
			int counter = 0;
			int fact = 1;
			for (int i = 1;; i++){
				fact *= i;
				counter++;
				if (fact == num){
					printf("%d = %d!\n", num, counter);
					break;
				}
				if (fact > num){
					printf("%d not factorial\n", num);
					break;
				}
			}
		}


	}
	return 0;
}

