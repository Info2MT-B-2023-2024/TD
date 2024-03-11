#include <stdio.h>
#include <stdlib.h>

#define MIN_VALUE -1.
#define MAX_VALUE 1.

double my_rand(const double val_min, const double val_max)
{
	return val_min + (val_max - val_min) * (rand() / (double)RAND_MAX);
}

int create_file_v3(const char *filename, const size_t num_points)
{
	FILE *f = NULL;
	const char data_type = 'd';
	size_t index = 0;
	double x = 0.;
	double y = 0.;
	double sum_x = 0.;
	double sum_y = 0.;
	double mean_x = 0.;
	double mean_y = 0.;

	srand(0);

	f = fopen(filename, "wb");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}

	if (1 != fwrite(&data_type, sizeof(char), 1, f))
	{
		fprintf(stderr, "error while writing header to %s.\n", filename);
		return 1;
	}
	if (1 != fwrite(&num_points, sizeof(size_t), 1, f))
	{
		fprintf(stderr, "error while writing header to %s.\n", filename);
		return 1;
	}

	printf("[create_file_v3] num_points = %zu\n", num_points);
	for (index = 0; index < num_points; index++)
	{
		x = my_rand(MIN_VALUE, MAX_VALUE);
		y = my_rand(MIN_VALUE, MAX_VALUE);
		sum_x += x;
		sum_y += y;

		if (1 != fwrite(&x, sizeof(double), 1, f))
		{
			fprintf(stderr, "error while write to %s.\n", filename);
			return 1;
		}
		if (1 != fwrite(&y, sizeof(double), 1, f))
		{
			fprintf(stderr, "error while write to %s.\n", filename);
			return 1;
		}
	}
	mean_x = sum_x / num_points;
	mean_y = sum_y / num_points;

	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}

int process_file_v3(const char *filename)
{
	FILE *f = NULL;
	size_t num_elem = 0;
	size_t index = 0;
	char file_type = 0;

	double sum_x = 0.;
	double mean_x = 0.;
	double sum_y = 0.;
	double mean_y = 0.;

	f = fopen(filename, "rb");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}

	if (1 != fread(&file_type, sizeof(char), 1, f))
	{
		fprintf(stderr, "error while reading header from %s.\n", filename);
		return 1;
	}
	if (file_type != 'd')
	{
		fprintf(stderr, "error while reading header from %s.\n", filename);
		return 1;
	}
	if (1 != fread(&num_elem, sizeof(size_t), 1, f))
	{
		fprintf(stderr, "error while reading header from %s.\n", filename);
		return 1;
	}
	printf("num_elem = %zu\n", num_elem);

	double *t = NULL; // address of the dynamic array
	t = (double *)malloc(2 * num_elem * sizeof(double));
	printf("t = %p\n", t);
	if (NULL == t)
	{
		fprintf(stderr, "error while allocating memory for x.\n");
		return 1;
	}

	if(2 * num_elem!=fread(t, sizeof(double), 2 * num_elem, f))
	{
		fprintf(stderr, "error while reading data from %s.\n", filename);
		free(t);
		return 1;
	}

	double *x = NULL; // address of the dynamic array
	x = (double *)malloc(num_elem * sizeof(double));
	printf("x = %p\n", x);
	if (NULL == x)
	{
		fprintf(stderr, "error while allocating memory for x.\n");
		free(t);
		return 1;
	}

	double *y = NULL; // address of the dynamic array
	y = (double *)malloc(num_elem * sizeof(double));
	printf("y = %p\n", y);
	if (NULL == y)
	{
		fprintf(stderr, "error while allocating memory for x.\n");
		free(t);
		free(x);
		return 1;
	}

	for (index = 0;index<num_elem;index++)
	{
		x[index] = t[2*index];
		y[index] = t[1+2*index];
	}
	
	sum_x = 0.;
	sum_y = 0.;
	for (index = 0; index < num_elem; index++)
	{
		sum_x += x[index];
		sum_y += y[index];
	}
	mean_x = sum_x / num_elem;
	mean_y = sum_y / num_elem;
	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

	free(t);
	free(x);
	free(y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}

int main(int argc, const char *argv[])
{

	const char *filename = "data/data.bin";
	int ret = 0;

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <num_points>\n", argv[0]);
		return 1;
	}

	const size_t num_points = atol(argv[1]);

	ret = create_file_v3(filename, num_points);
	if (ret != 0)
	{
		return ret;
	}

	ret = process_file_v3(filename);
	if (ret != 0)
	{
		return ret;
	}

	return 0;
}