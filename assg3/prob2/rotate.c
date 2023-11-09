#include <stdio.h>
#include <stdlib.h>


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

void swap(int *x, int* y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

int* rotateArr(int rotation, int size, int array[]){
	int* newArray = malloc(size*sizeof(int));
	if (rotation != 0){
		for (int i=0; i < size; ++i){
			int adjRotate = (i + rotation) % size;
			adjRotate = (adjRotate + size) % size;
			newArray[adjRotate] = array[i];
		}

	}

	return newArray;
}

void printArr(int size, int array[]){
	for (int i=0; i < size; ++i){
		printf("%d", array[i]);
	}
	printf("\n");

}

int main(){
	int size, *array, rotation;

	if (scanf("%d", &size) != 1 || size <= 0){
		fprintf(stderr, "Bad input (i.e. non number entered)\n");
		return(1);
	}

	array = readArr(size);

	if (scanf("%d", &rotation) != 1){
		fprintf(stderr, "Bad input (i.e. non number entered)\n");
		return(1);
	}

	int* rotated = rotateArr(rotation, size, array);
	
	printArr(size, rotated);
}
