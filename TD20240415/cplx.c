#include <stdio.h>
#include "cplx.h"  // in .

void init_cplx(cplx *c) {
    c->real = 0.;
    c->img = 0.;
    return;
}

void display_cplx(const cplx c){
    printf(".r = %+6.3lf\n", c.real);
    printf(".i = %+6.3lf\n", c.img);
    return;
}