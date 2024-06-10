#pragma once
#include "error.h"
#include "node.h"

typedef struct
{
	node *head; // or first
	node *tail; // or last

} list;

void init_list(list *l);
void insert_node_at_tail(list *l, node *n);
void insert_node_at_head(list *l, node *n);
void display_list(list l);
void insert_node_at_index(list *l, node *n, int index);
void delete_at_index_list(list *l, int index);