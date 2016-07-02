#include <stdio.h>
#include <stdlib.h>

struct stack_node
{
	int data;
	struct stack_node *next;
};

class Stack 
{
	stack_node *top = NULL;

	public:

		struct stack_node *get_node(int value)
		{
			struct stack_node *new_node;
			new_node = (struct stack_node *)malloc(sizeof(struct stack_node));
			new_node->data = value;
			new_node->next = NULL;
			return new_node;
		}

		void push_to_stack(int value)
		{
			struct stack_node *new_node;
			new_node = get_node(value);
			new_node->next = top;
			top = new_node;
		}

		int pop_from_stack()
		{
			int pop_value = top->data;
			top = top->next;
			return pop_value;
		}

		int peek_of_stack()
		{
			if (top!=NULL)
				return top->data;
			return NULL;
		}
};

class Queue	
{
	private:
		Stack stack1;
		Stack stack2;
	public:
		void enqueue(int value)
		{
			stack1.push_to_stack(value);
		}
		int dequeue()
		{
			if (stack2.peek_of_stack() == NULL)
			{
				while (stack1.peek_of_stack() != NULL)
					stack2.push_to_stack(stack1.pop_from_stack());
			}
			return stack2.pop_from_stack();
		}
};

int main()
{
	Queue queue_object;
	int queue_data[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, queue_size = 10;
	for (int index = 0; index < 10; index++)
		queue_object.enqueue(queue_data[index]);
	for (int index = 0; index < 10; index++)
		printf("%d\n", queue_object.dequeue());
	getchar();
	return 0;
}
