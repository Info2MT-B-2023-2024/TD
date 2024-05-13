#include "list.h"

int main(int argc, const char *argv[])
{
	list l;
	element e;

	init_list(&l);
	display_list(l);

	e.x = 1.;
	e.y = 1.;
	insert(&l, e, 0);
	display_list(l);

	e.x = 2.;
	e.y = 2.;
	insert(&l, e, 1);
	display_list(l);

	e.x = 3.;
	e.y = 3.;
	insert(&l, e, 2);
	display_list(l);

	e.x = 0.;
	e.y = 0.;
	insert(&l, e, 0);
	display_list(l);

	return 0;
}