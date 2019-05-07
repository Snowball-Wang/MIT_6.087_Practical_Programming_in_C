#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode
{
	int data;
	struct tnode* left;
	struct tnode* right;
};

struct tnode* talloc(int data)
{
	struct tnode* p = (struct tnode*)malloc(sizeof(struct tnode));
	if (p != NULL)
	{
		p->data = data;
		p->left = NULL;
		p->right = NULL;
	}
	return p;
}

struct tnode* addnode(struct tnode* root, int data)
{
	struct tnode* p = NULL;
	/* termination condition */
	if (root == NULL)
	{
		/* allocate node */
		p = talloc(data);
		root = p;
		/* return new root */
		return root;
	}
	/* recursive call */
	else if (data < root->data)
		root->left = addnode(root->left, data);
	else
		root->right = addnode(root->right, data);
}

void preorder(struct tnode* root)
{
	struct tnode* curr = root;
	if (curr != NULL)
	{
		printf("%d ", curr->data);
		preorder(curr->left);
		preorder(curr->right);
	}
}

void inorder(struct tnode* root)
{
	struct tnode* curr = root;
	if (curr != NULL)
	{
		inorder(curr->left);
		printf("%d ", curr->data);
		inorder(curr->right);
	}
}

void postorder(struct tnode* root)
{
	struct tnode* curr = root;
	if (curr != NULL)
	{
		postorder(curr->left);
		postorder(curr->right);
		printf("%d ", curr->data);
	}
}

int deltree(struct tnode* root)
{
	int count = 0;
	struct tnode* curr = root;
	if (curr != NULL)
	{
		count += deltree(curr->left);
		count += deltree(curr->right);
		curr->left = NULL;
		curr->right = NULL;
		free(curr);
		curr = NULL;
		count++;
	}
	return count;
}

int main(void)
{
	/* test addnode and talloc */
	struct tnode* root = NULL;
	int num[] = {3, 1, 0, 2, 8, 6, 5, 9};
	for (int i = 0; i < 8; i++)
		root = addnode(root, num[i]);

	/* test preorder */
	puts("test preorder...");
	puts("should display: 3 1 0 2 8 6 5 9");
	preorder(root);
	printf("\n");

	/* test inorder */
	puts("test inorder...");
	puts("should display: 0 1 2 3 5 6 8 9");
	inorder(root);
	printf("\n");

	/* test postorder */
	puts("test postorder...");
	puts("should display: 0 2 1 5 6 9 8 3");
	postorder(root);
	printf("\n");

	/* test deltree */
	int number = 0;
	puts("test deltree...");
	puts("should display: 8");
	number = deltree(root);
	printf("%d\n", number);

	return 0;
}
