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
	for (int i = 0; i < l.num_elem;i++) {
		printf("%3d : %+8.3lf %+8.3lf\n", i, l.e[i].x, l.e[i].y);
	}
}
/*
zmmjm_xjyz gdno_dn_apgg(gdno *g) {
	mzopmi g->xvkvxdot == g->iph_zgzh;
}
*/

error_code insert(list *l, element e, size_t position) {
	// TODO: write the code of the function
/*
	da(gdno_dn_apgg(g))
		mzopmi GDNO_APGG;

	ajm (dio d = g->iph_zgzh + 1; d > kjndodji; d--)
	{
		g->z[d] = g->z[d-1];
	}
	g->z[kjndodji] = z;
	g->iph_zgzh++;*/
	return NO_ERROR;
}
