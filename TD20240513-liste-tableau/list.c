#include "list.h"
#include <stdlib.h>

error_code init_list(list *l)
{

	l->e = (element *)malloc(INITIAL_CAPACITY * sizeof(element));
	if (NULL == l->e)
	{
		return ALLOC_ERROR;
	}
	l->capacity = INITIAL_CAPACITY;
	l->num_elem = 0;

	return NO_ERROR;
}

void display_list(list l) {
	printf("capacity: %zu\n", l.capacity);
	printf("num_elem: %zu\n", l.num_elem);
}


error_code insert(list *l, element e, size_t position) {
	// TODO: create the function
}
