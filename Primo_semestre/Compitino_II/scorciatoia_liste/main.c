#include<stdio.h>
#include<stdlib.h>

typedef struct node node_t;
typedef struct node {
	// Campi base
	int data;
	node_t* next;

	// Campo scorciatoia
	node_t* skip;
} node_t;

node_t* find (node_t* head, int value) {
	while (head)
	{
		if(head->data == value) return head;
		if(head->skip && head->skip->data <= value)
			head = head->skip;
		else
			head = head->next;
	}
	return NULL;
}


int main() {
	// Esempio di utilizzo
	node_t n3 = {30, NULL, NULL};
	node_t n2 = {20, &n3, NULL};
	node_t n1 = {10, &n2, &n3}; // Scorciatoia da n1 a n3
	node_t* head = &n1;

	int value_to_find = 30;
	node_t* result = find(head, value_to_find);
	if (result != NULL) {
		printf("Valore %d trovato nella lista.\n", result->data);
	} else {
		printf("Valore %d non trovato nella lista.\n", value_to_find);
	}

	return 0;
}