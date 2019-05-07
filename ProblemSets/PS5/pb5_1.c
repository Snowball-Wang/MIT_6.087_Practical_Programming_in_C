#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int data;
	struct node* next;
};

struct node* nalloc(int data)
{
	struct node* p = (struct node*)malloc(sizeof(struct node));
	if (p != NULL)
	{
		p->data = data;
		p->next = NULL;
	}
	return p;
}

struct node* addfront(struct node* head, int data)
{
	struct node* p = nalloc(data);
	if (p == NULL) return head;
	p->next = head;
	return p;
}

void display(struct node* head)
{
	struct node* p = head;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

struct node* addback(struct node* head, int data)
{
	struct node* p = nalloc(data);
	struct node* curr = NULL;
	/* consider empty list */
	if (head == NULL)
		head = p;
	else
	{
		curr = head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = p;
		p->next = NULL;
	}
	return head;
}

void freelist(struct node* head)
{
	struct node* curr = NULL;
	while (head != NULL)
	{
		curr = head;
		head = head->next;
		free(curr);
	}
}

struct node* find(struct node* head, int data)
{
	struct node* curr = NULL;
	curr = head;
	while (curr != NULL)
	{
		if (curr->data == data)
			return curr;
		curr = curr->next;
	}
	return NULL; /* if not found, return NULL */
}

struct node* delnode(struct node* head, struct node* pelement)
{
	struct node* curr = NULL;
	/* if pelement is head */
	if (pelement == head)
	{
		head = head->next;
		free(pelement);
		pelement = NULL;
	}
	else
	{
		curr = head;
		while (curr != NULL)
		{
			if (curr->next == pelement)
			{
				curr->next = pelement->next;
				pelement->next = NULL;
				free(pelement);
			}
			curr = curr->next;
		}
	}
	return head;
}

int main(void)
{
	struct node* head = NULL;

	/* test addfront and display */
	puts("test addfront and display");
	head = addfront(head, 1);
	head = addfront(head, 2);
	puts("should display: 2 1");
	display(head);

	/* test freelist */
	puts("test freelist");
	freelist(head);
	head = NULL;
	puts("should display: ");
	display(head);
	
	/* test addback */
	puts("test addback");
	head = addback(head, 1);
	head = addback(head, 2);
	puts("should display: 1 2");
	display(head);

	/* test find */
	puts("test find");
	struct node* n1 = NULL;
	/* test find whether value is found or not */
	// n1 = find(head, 0); /* test when value not found */
	n1 = find(head, 2);
	if (n1 == NULL)
		puts("value not found");
	else
		puts("value found");
	
	/* test delnode */
	puts("test delnode");
	head = delnode(head, n1);
	puts("should display: 1 ");
	display(head);

	/* test freelist again */
	puts("test freelist again");
	freelist(head);
	head = NULL;
	puts("should display: ");
	display(head);

	return 0;
}



















