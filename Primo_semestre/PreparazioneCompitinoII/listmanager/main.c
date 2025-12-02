#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int v; struct Node *next;
} Node;

void push_front(Node **head, int v){
	Node *n = malloc(sizeof(*n));
	if(!n){perror("malloc"); exit(1);} 
	n->v=v; n->next=*head; *head=n;
}

void print(const Node *h){
	for(;h;h=h->next) printf("%d ", h->v);
	printf("\n");
}

void reverse(Node **head){
	Node *prev=NULL, *cur=*head, *nx;
	while(cur){ nx=cur->next; cur->next=prev; prev=cur; cur=nx; }
	*head=prev;
}

void remove_all(Node **head, int x){
	Node **pp = head; 
	while(*pp){
		if((*pp)->v == x){
			Node *tmp = *pp; *pp = (*pp)->next; free(tmp);
		} else {
			pp = &((*pp)->next);
		}
	}
}

void free_all(Node *h){
	while(h){ Node *t=h; h=h->next; free(t);} }

int main(int argc, char **argv){
	if(argc!=2){fprintf(stderr,"Uso: %s <x>\n",argv[0]);return 1;}
	int x = atoi(argv[1]);
	Node *head=NULL; int val;
	while (scanf("%d", &val)==1) push_front(&head, val);
	print(head);
	remove_all(&head, x); print(head);
	reverse(&head); print(head);
	free_all(head); return 0;
}