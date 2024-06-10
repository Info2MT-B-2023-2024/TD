#include "node.h"
#include <stdlib.h>
#include <stdio.h>

node *create_node(element e)
{
	node *new_node = (node *)malloc(sizeof(node));
	if (new_node == NULL)
	{
		return NULL;
	}
	new_node->e = e;
	new_node->previous = NULL;
	new_node->next = NULL;
	return new_node;
}
void free_node(node *n)
{
	//free_element(n->e); useful if e is a pointer
	if (n == NULL)
	{
		fprintf(stderr, "free_node: NULL pointer\n");
		return;
	}
	free(n);
	return;
}

void display_node(node *n)
{
	printf("node:     %p\n", n);
	if (n == NULL)
	{
		return;
	}

	printf("e:        ");
	display_element(n->e);
	printf("previous: %p\n", n->previous);
	printf("next:     %p\n", n->next);
	return;
}