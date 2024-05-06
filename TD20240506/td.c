#include <stdio.h>
#include <math.h>

// DEBUG=0 => no display
// DEBUG=1 => display results
// DEBUG=2 => display all steps

#define DEBUG 1
#define X "IL FAIT BEAU ET CHAUD"

int main(int argc, const char *argv[])
{
	double a = -1.;
	double b = -2.;
	double c = 3.;
	double delta = 0.;
	double x1 = 0.;
	double x2 = 0.;

	const int Y = X;

	delta = b * b - 4 * a * c;
#if DEBUG==2
	printf("a=%+8.3lf\n", a);
	printf("b=%+8.3lf\n", b);
	printf("c=%+8.3lf\n", c);
#endif
#if DEBUG>0
	printf("delta=%+8.3lf\n", delta);
#endif
	if (delta >= 0)
	{
		x1 = -b + sqrt(delta) / (2. * a);
		x2 = -b - sqrt(delta) / (2. * a);
		printf("x1=%+8.3lf\n", x1);
		printf("x2=%+8.3lf\n", x2);
	}
	else
	{
		printf("No real solution.");
	}

#define SUN

#ifdef SUN
	puts("Die Sonne scheine");
#endif

#undef SUN

#ifdef SUN
	puts("Le zoleil brille");
#endif





	return 0;
}

/*
#define CLOUD
#define RAIN 1


//#define DEBUG


int main(int argc, const char *argv[])
{
#ifdef CLOUD
	int cloud = 0;
#else
	int sun = 1;
#endif

#ifndef CLOUD
//
#endif

#ifdef DEBUG
	printf("%d", RAIN);
#endif
//#error "VERY NICE ERROR"
	return 0;
}*/
