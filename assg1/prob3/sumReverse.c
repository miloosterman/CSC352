/*
 * File: findRev.c
 * Author: Milo Osterman
 * Purpose: Read in a number and print the sum of the number and its reversal
 */

#include <stdio.h>
// Takes an input of an integer and reverses its value mathematically
int findRev(int num){
	int origNum = num;
	int reverse = 0;
	int last = 0;
	while (num > 0){
		last = num % 10;
		reverse = (reverse * 10) + last;
		num = num / 10;
	}
	return reverse + origNum;
}


int main(){
	int num = 0;
	int res = 0;
	int status = 0;
	while(status != -1){
                status = scanf("%d", &num);
                if (status == 0){
                        fprintf(stderr,"Error: input is not a number\n");
                        return 1;
		} else if (status == -1){
			break;
                } else if (num < 1){
                        fprintf(stderr, "Error: input value %d is not positive\n", num);
		} else{
			res = findRev(num);
			printf("%d\n", res);
		}

	}

	return 0;
}



