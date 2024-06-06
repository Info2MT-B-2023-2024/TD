#pragma once

#include <stdio.h>
#include "error.h"

typedef enum
{
	LAST_POS=-1,
	FIRST_POS=0
} position;

typedef struct
{
	double x;
	double y;
} point2D;

typedef point2D element;

typedef struct node {
	element e;
	struct node *prev;
	struct node *next;
} node;

typedef struct
{
	node *first;
	node *last;
	size_t num_elem;
} list;

error_code init_list(list *l);
error_code insert(list *l, element e, int pos);
