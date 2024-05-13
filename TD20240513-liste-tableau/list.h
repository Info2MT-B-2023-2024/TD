#pragma once

#include <stdio.h>
#include "error.h"

#define INITIAL_CAPACITY 5

typedef struct
{
	double x;
	double y;
} point2D;

typedef point2D element;

typedef struct
{
	element *e;
	size_t num_elem;
	size_t capacity;
} list;

error_code init_list(list *l);
void display_list(list l);
error_code insert(list *l, element e, size_t position);
