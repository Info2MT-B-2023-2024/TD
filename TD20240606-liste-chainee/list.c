#include "list.h"
#include <stdio.h>

void init_list(list *l)
{
	l->head = NULL;
	l->tail = NULL;
	return;
}

void insert_node_at_tail(list *l, node *n) {
	if (l->head == NULL)
	{
		l->head = n;
		l->tail = n;
		return;
	}
	l->tail->next = n;
	n->previous = l->tail;
	l->tail = n;
	n->next = NULL;
	return;
}

void insert_node_at_head(list *l, node *n) {
	if (l->head == NULL)
	{
		l->head = n;
		l->tail = n;
		return;
	}
	l->head->previous = n;
	n->next = l->head;
	l->head = n;
	n->previous = NULL;
	return;
}

void insert_node_at_index(list *l, node *n, int index) {
	if (index == 0)
	{
		insert_node_at_head(l, n);
		return;
	}
	if ( index == -1 )
	{
		insert_node_at_tail(l, n);
		return;
	}
	node *current = l->head;
	size_t current_index = 0;
	while (current != NULL)
	{
		if (current_index == index)
		{
			printf("insert_node_at_index: prev = %p\n", current->previous);
			printf("insert_node_at_index: next = %p\n", current);
			n->previous = current->previous;
			n->next = current;
			current->previous->next = n;
			current->previous = n;
			return;
		}
		current = current->next;
		current_index++;
	}
	return;
}
void delete_head_list(list *l)
{
	if (l->head == NULL)
	{
		return;
	}
	node *n = l->head;
	l->head = l->head->next;
	if (l->head == NULL)
	{
		l->tail = NULL;
	}
	else
	{
		l->head->previous = NULL;
	}
	free_node(n);
	return;
}

void delete_tail_list(list *l)
{
	if (l->tail == NULL)
	{
		return;
	}
	node *n = l->tail;
	l->tail = l->tail->previous;
	if (l->tail == NULL)
	{
		l->head = NULL;
	}
	else
	{
		l->tail->next = NULL;
	}
	free_node(n);
	return;
}

void delete_at_index_list(list *l, int index)
{
	if(index==0) {
		delete_head_list(l);
	}
	else if (index==-1)	{
		delete_tail_list(l);
	}
	node *current = l->head;
	size_t node_index = 0;
	while (current != NULL)
	{
		if (node_index == index)
		{
			current->previous->next = current->next;
			current->next->previous = current->previous;
			free_node(current);
			return;
		}
		node_index++;
		current = current->next;
	}
	return;
}
void display_list(list l)
{
	printf("list\n");
	printf("head:        %p\n", l.head);
	printf("tail:        %p\n", l.tail);
	printf("content:\n");
	node *current = l.head;
	size_t node_index = 0;
	while (current != NULL)
	{
		printf("*** node[%zu] ***\n", node_index++);
		display_node(current);
		current = current->next;
	}
	return;
}
