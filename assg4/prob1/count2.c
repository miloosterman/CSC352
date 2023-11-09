#include <stdio.h>
#include <stdlib.h>

struct node {
       int* val;
       struct node* next;
};       

struct node* head = NULL;

struct node* read_int(){
	struct node* tempNode;
	int* tempInt = malloc(sizeof(int));
	int status;
	
	status = scanf("%d", tempInt);
	if (status == EOF){
		return NULL;
	} else if (status != 1){
		fprintf(stderr, "Non-integer value entered\n");
		exit(1);
	}
	tempNode = malloc(sizeof(struct node));
	if (tempNode == NULL){
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}

	tempNode->val = tempInt;
	tempNode->next = head;
	head = tempNode;

	return tempNode;

}

void sort_list(){
	struct node* ptr1;
	struct node* ptr2;
	int* temp = malloc(sizeof(int));

	for (ptr1 = head; ptr1; ptr1 = ptr1->next){
		for (ptr2 = ptr1->next; ptr2; ptr2 = ptr2->next){
			if (*(ptr1->val) > *(ptr2->val)){
				temp = ptr1->val;
				ptr1->val = ptr2->val;
				ptr2->val = temp;
			}
		}
	}
}

void print_list(){
	struct node* ptr;
	int count = 1;

	for (ptr = head; ptr; ptr = ptr->next){
		struct node* next = ptr->next;
		if (next && *(ptr->val) == *(next->val)){
			count++;
		} else {
			printf("%d %d\n", *(ptr->val), count);
			count = 1;
		}

	}
}

int main(){
	while (read_int() != NULL){
	}

	sort_list();
	print_list();
}


