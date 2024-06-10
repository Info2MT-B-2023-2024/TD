#pragma once
#include "element.h"

typedef struct node
{
	element e;
	struct node *previous;
	struct node *next;
} node;

node *create_node(element e);
void free_node(node *n);
void display_node(node *n);
