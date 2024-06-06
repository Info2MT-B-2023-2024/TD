#include "list.h"
#include <stdlib.h>

error_code init_list(list *l)
{
	l->first = NULL;
	l->last = NULL;
	l->num_elem = 0;
	return NO_ERROR;
}

error_code insert(list *l, element e, int pos) {

	// check de pos en fonction de l->num_elem

	// create the new node
	node *n = (node *)malloc(sizeof(node));
	if(NULL==n) {
		printf("Error malloc new node");
		return ALLOC_ERROR;
	}
	memcpy(&(n->e), &e, sizeof(element));

	// manage insertion position
	switch(pos) {
		// cas insert debut
		case FIRST_POS:
			l->first->prev = n;
			n->next = l->first;
			n->prev = NULL;
			l->first = n;
			break;
		// cas insert fin
		case LAST_POS:
			n->prev = l->last;
			l->last->next = n;
			l->last = n;
			n->next = NULL;
			break;
		// cas insert entre les deux
		default:
			node *p = l->first;
			//for (int i = 0; i < pos;p=p->next, i++);
			for (int i = 0; i < pos;i++) {
				p = p->next;
			}
			node *prev_node = p->prev;
			node *next_node = p;
			prev_node->next = n;
			next_node->prev = n;
			n->prev = prev_node;
			n->next = next_node;
			break;
	}
	l->num_elem++;
}