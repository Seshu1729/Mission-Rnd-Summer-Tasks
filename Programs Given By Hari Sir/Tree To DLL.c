#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct tree_node
{
	int data;
	struct tree_node *left;
	struct tree_node *right;
};


struct tree_node *get_tree_node(int data)
{
	struct tree_node *new_tree_node;
	new_tree_node = (struct tree_node *)malloc(sizeof(struct tree_node));
	new_tree_node->data = data;
	new_tree_node->left = NULL;
	new_tree_node->right = NULL;
	return new_tree_node;
}

void inorder(struct tree_node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void print_linked_list(struct tree_node *head)
{
	while (head != NULL)
	{
		printf("%d ", head->data);
		head = head->right;
	}
}

struct tree_node *insert(struct tree_node *root, int data)
{
	struct tree_node *head = root;
	if (root == NULL)
		root = get_tree_node(data);
	else
	{
		if (root->data > data)
			root->left = insert(root->left, data);
		else
			root->right = insert(root->right, data);
	}
	return root;
}

struct tree_node *create_tree(int tree_data[], int tree_size)
{
	struct tree_node *root = NULL;
	for (int index = 0; index < tree_size; index++)
	{
		root = insert(root, tree_data[index]);
	}
	return root;
}

void change_tree_to_linked_list(struct tree_node *root, struct tree_node **head)
{
	if (root != NULL)
	{
		change_tree_to_linked_list(root->left, head);
		head = &root;
		change_tree_to_linked_list(root->right, head);
	}
}

int main()
{
	int tree_data[10] = { 6, 4, 8, 9, 2, 0, 1, 3, 5, 7 }, tree_size = 10;
	struct tree_node *root = create_tree(tree_data, tree_size);
	struct tree_node *head = NULL;
	//inorder(root);
	change_tree_to_linked_list(root, &head);
	print_linked_list(head);
	getchar();
	return 0;
}