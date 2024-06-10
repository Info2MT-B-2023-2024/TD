#include "list.h"
#include "element.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	node *n = NULL;
	list l;

	init_list(&l);

	n = create_node(10);
	insert_node_at_tail(&l, n);

	n = create_node(20);
	insert_node_at_tail(&l, n);

	n = create_node(5);
	insert_node_at_head(&l, n);

	n = create_node(3);
	insert_node_at_head(&l, n);
	display_list(l);

	n = create_node(7);
	insert_node_at_index(&l, n, 2);
	display_list(l);

	puts("\nDelete at index 2...");
	delete_at_index_list(&l,2);
	display_list(l);
	return 0;
}
