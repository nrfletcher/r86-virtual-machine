#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct stack_node {
	int is_head;
	char token[12];
	struct stack_node *prev;
	struct stack_node *next;
} stack_node;

int stcksize(stack_node *head) {
        if(head == NULL) return 0;
        stack_node *curr = head;
        int len = 1;
        while(curr->prev != NULL) {
                len++;
                curr = curr->prev;
        }
        return len;
}

stack_node *push(stack_node *head, char *token) {
	if(head == NULL) {
		head = (stack_node *) malloc(sizeof(stack_node));
		strcpy(head->token, token);
		head->prev = NULL;
		head->next = NULL;
		head->is_head = 1;
		return head;
	} else {
		stack_node *curr = (stack_node *) malloc(sizeof(stack_node));
		strcpy(curr->token, token);
		curr->prev = head;
		curr->next = NULL;
		head->next = curr;
		head->is_head = 0;
		curr->is_head = 1;
		return curr;
	}
}

stack_node *pop(stack_node *head) {
	if(head == NULL) return NULL;
	
	if(head->prev == NULL) {
		free(head);
		return NULL;
	} else {
		stack_node *prev = head->prev;
		prev->next = NULL;
		free(head);
		return prev;
	}
}

int peek(stack_node *head, char *stoken) {
	if(head == NULL) return 1;
	strcpy(stoken, head->token);
	return 0;
}

int pstack(stack_node *head) {
	if(head == NULL) {
		puts("[ ]");
		return 0;
	}
	
	stack_node *curr = head;
	while(1) {
		if(curr->prev == NULL) break;
		curr = curr->prev;
	}
	
	printf("[ ");
	while(curr != NULL) {
		printf("%s", curr->token);
		curr = curr->next;
		if(curr != NULL) printf(", ");
	}	
	printf(" ]\n");
	return 0;
}

void freestack(stack_node *head) {
        stack_node *curr = head;
	stack_node *next;
        
	while(curr != NULL) {
		next = curr->prev;
		free(curr);
		curr = next;
	}
}

char *itoa(int num, char *s) {
	if(s == NULL) return NULL;
	sprintf(s, "%d", num);
	return s;
}
