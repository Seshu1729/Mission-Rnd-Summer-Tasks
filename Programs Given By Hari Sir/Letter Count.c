#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define char_to_int(c) (c - 'a')
#define buffer_size 128

struct trie_node
{
	struct trie_node *children[26];
	int value;
	bool is_valid_word;
};

struct trie_node *get_node()
{
	struct trie_node *new_node = NULL;
	new_node = (struct trie_node *)malloc(sizeof(struct trie_node));
	if (new_node!=NULL)
	{
		new_node->is_valid_word = false;
		new_node->value = 0;
		for (int i = 0; i < 26; i++)
			new_node->children[i] = NULL;
	}
	return new_node;
}

void insert(struct trie_node *root, const char *key)
{
	int level, length = strlen(key), index;
	struct trie_node *travel_node = root;

	for (level = 0; level < length; level++)
	{
		index = char_to_int(key[level]);
		if (!travel_node->children[index])
			travel_node->children[index] = get_node();

		travel_node = travel_node->children[index];
	}
	travel_node->is_valid_word = true;
	travel_node->value++;
}

void letter_count(char *file_name, int count)
{
	struct trie_node *root = NULL;
	char buffer[buffer_size];
	FILE *file_pointer = fopen(file_name, "r");
	while (fgets(buffer, buffer_size, file_pointer))
		insert(root, buffer);
}

int main()
{
	letter_count("sample.txt", 3);
	getchar();
	return 0;
}
