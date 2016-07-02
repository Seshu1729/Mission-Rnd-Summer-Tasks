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
	struct node *head = root;
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

int main()
{
	int tree_data[10] = { 6, 4, 8, 9, 2, 0, 1, 3, 5, 7 }, tree_size = 10;
	struct node *root = create_tree(tree_data, tree_size);
	preorder(root);
	getchar();
	return 0;
}