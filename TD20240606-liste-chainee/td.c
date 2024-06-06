#include "list.h"

int main(int argc, const char *argv[])
{
	list l;
	element e;

	init_list(&l);

	e.x = 1.;
	e.y = 2.;
	insert(&l, e, FIRST_POS);
	return 0;
}