#include <stdio.h> // in /usr/include
#include "cplx.h"  // in .



int main(int argc, const char *argv[])
{
	cplx c1 = {.real = 4., .img = 2.};
	init_cplx(&c1);
	display_cplx(c1);
	// .r = +0.000
	// .i = +0.000
	return 0;
}