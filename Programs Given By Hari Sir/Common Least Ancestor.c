#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};

struct node *get_node(int data)
{
	struct node *new_node;
	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->left = NULL;
	new_node ->right = NULL;
	return new_node;
}

void preorder(struct node* root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

struct node *inorder_successor(struct node *root)
{
	struct node* head = root;
	while (head->left != NULL)
		head = head->left;
	return head;
}

struct node *insert(struct node *root, int data)
{
	if (root == NULL)
		root = get_node(data);
	else
	{
		if (root->data > data)
			root->left = insert(root->left, data);
		else
			root->right = insert(root->right, data);
	}
	return root;
}

struct node *delete_node(struct node *root, int data)
{
	if (root != NULL)
	{
		if (root->data < data)
			root->left = delete_node(root, data);
		else if (root->data>data)
			root->right = delete_node(root, data);
		else
		{
			if (root->left == NULL&&root->right == NULL)
				root = NULL;
			else if (root->left == NULL)
				return root->right;
			else if (root->right == NULL)
				return root->left;
			else
			{
				struct node *inorder_succ = inorder_successor(root->right);
				root->data = inorder_succ->data;
				root->right = delete_node(root->right, inorder_succ->data);
			}
		}
	}
	return root;
}

struct node *create_tree(int tree_data[], int tree_size)
{
	struct node *root = NULL;
	for (int index = 0; index < tree_size; index++)
	{
		root = insert(root, tree_data[index]);
	}
	return root;
}

int CLA(struct node *root, int value1, int value2)
{
	if (root != NULL)
	{
		if (root->data>=value1&&root->data <= value2)
			return root->data;
		else if (root->data<value2)
			return CLA(root->right, value1, value2);
		else if (root->data>value1)
			return CLA(root->left, value1, value2);
	}
	return -1;
}

int main()
{
	int tree_data[10] = { 6, 4, 8, 9, 2, 0, 1, 3, 5, 7 }, tree_size = 10;
	struct node *root = create_tree(tree_data, tree_size);
	preorder(root);
	printf("\nCLA for 1 and 9 is :: %d", CLA(root, 1, 9));
	printf("\nCLA for 3 and 5 is :: %d", CLA(root, 3, 5));
	printf("\nCLA for 7 and 9 is :: %d", CLA(root, 7, 9));
	printf("\nCLA for 6 and 9 is :: %d", CLA(root, 6, 9));
	printf("\nCLA for 10 and 15 is :: %d", CLA(root, 10, 15));
	getchar();
	return 0;
}