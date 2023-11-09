/*
 * File: count.c
 * Author: Milo Osterman
 * Purpose: This program reads in a sequence of integers and counts the 
 * occurences of each integer value in the sequence, printing the result  
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
/*
 * readArr(size) -- takes a size parameter and reads in values as input
 * until the size of the array is equal to the size given. An error
 * occurs if too few integers are provided
 */
int* readArr(int size){
        int* array = malloc(size*sizeof(int));

        if (array == NULL){
                fprintf(stderr, "Out of memory\n");
                exit(1);
        }

        for (int i=0; i < size; ++i){
                if(scanf("%d", &array[i]) != 1){
                        fprintf(stderr, "Input was not %d integers\n", size);
                        exit(1);
                }
        }
        return array;
}

/*
 * swap(x, y) -- takes two integer memory addresses and swaps them
 */
void swap(int *x, int* y){
        int temp = *x;
        *x = *y;
        *y = temp;
}
/*
 * sort(size, array) -- takes a size integer and array and sorts it 
 * in ascending order using bubble sort
 */
void sort(int size,int array[]){
        for (int i=0; i < size - 1; ++i){
                for (int j=0; j < size - i - 1; ++j){
                        if (array[j] > array[j+1]){
                                swap(&array[j], &array[j + 1]);

                        }
                }
        }
}
/*
 * printOcc(size, array) -- Prints the number of occurences each integer
 * appears in the array provided
 */
void printOcc(int size, int array[]){
        for (int i=0; i < size; ++i){
                int count = 1;
                while(array[i] == array[i+1]){
                        count++;
                        i++;
                }
                printf("%d %d\n", array[i], count);
        }
}


int main(){
        int size, *array;

        if (scanf("%d", &size) != 1 || size <= 0){
                fprintf(stderr, "Bad input (i.e. non number entered)\n");
                return(1);
        }

        array = readArr(size);
        sort(size, array);
"count.c" 87L, 1729C                                                                                                                          11,1          Top
