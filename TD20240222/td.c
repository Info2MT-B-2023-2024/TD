// files and directories organisation
// file types (text, binary)
// filename and path (relative, absolute)
// file access modes (read, write, append)
// access mechanisms (open, close, read, write, seek, tell)
// always check errors

#include <stdio.h>
#include <stdlib.h>

#define NUM_POINTS 20000
#define MIN_VALUE -1.
#define MAX_VALUE 1.

double my_rand(const double val_min, const double val_max)
{
	return val_min + (val_max - val_min) * (rand() / (double)RAND_MAX);
}

int main(int argc, const char *argv[])
{
	const char *filename = "data/points2D.txt";
	FILE *f = NULL;
	size_t index = 0;
	double x = 0.;
	double y = 0.;

	srand(0);

	f = fopen(filename, "w");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}

	for (index = 0; index < NUM_POINTS; index++)
	{
		x = my_rand(MIN_VALUE, MAX_VALUE);
		y = my_rand(MIN_VALUE, MAX_VALUE);

		fprintf(f, "%+6.3lf %+6.3lf\n", x, y);
	}

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}