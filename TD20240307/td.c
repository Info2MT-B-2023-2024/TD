#include <stdio.h>
#include <stdlib.h>

#define NUM_POINTS 20000
#define MIN_VALUE -1.
#define MAX_VALUE 1.

double my_rand(const double val_min, const double val_max)
{
	return val_min + (val_max - val_min) * (rand() / (double)RAND_MAX);
}

int create_file(const char *filename)
{
	FILE *f = NULL;
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

	for (index = 0; index < NUM_POINTS; index++)
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
	mean_x = sum_x / NUM_POINTS;
	mean_y = sum_y / NUM_POINTS;

	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}

int process_file(const char *filename)
{
	FILE *f = NULL;
	size_t filesize = 0;
	size_t num_elem = 0;
	size_t index = 0;
	double x = 0.;
	double y = 0.;
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

	fseek(f, 0, SEEK_END);
	filesize = ftell(f);
	printf("filesize = %zu\n", filesize);
	num_elem = filesize / (2 * sizeof(double));
	printf("num_elem = %zu\n", num_elem);

	rewind(f); // DO NOT FORGET :)

	for (index = 0; index < num_elem; index++)
	{
		if (1 != fread(&x, sizeof(double), 1, f))
		{
			fprintf(stderr, "error while reading x from %s.\n", filename);
			return 1;
		}
		if (1 != fread(&y, sizeof(double), 1, f))
		{
			fprintf(stderr, "error while reading y from %s.\n", filename);
			return 1;
		}
		sum_x += x;
		sum_y += y;
	}

	mean_x = sum_x / num_elem;
	mean_y = sum_y / num_elem;

	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}
	return 0;
}

int create_file_v2(const char *filename)
{
	FILE *f = NULL;
	const char data_type = 'd';
	const size_t num_points = NUM_POINTS;
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

	// ---

	for (index = 0; index < NUM_POINTS; index++)
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
	mean_x = sum_x / NUM_POINTS;
	mean_y = sum_y / NUM_POINTS;

	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}

	return 0;
}

int process_file_v2(const char *filename)
{
	FILE *f = NULL;
	size_t num_elem = 0;
	size_t index = 0;
	char file_type = 0;

	double x = 0.;
	double y = 0.;
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
	if(file_type != 'd')
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


	for (index = 0; index < num_elem; index++)
	{
		if (1 != fread(&x, sizeof(double), 1, f))
		{
			fprintf(stderr, "error while reading x from %s.\n", filename);
			return 1;
		}
		if (1 != fread(&y, sizeof(double), 1, f))
		{
			fprintf(stderr, "error while reading y from %s.\n", filename);
			return 1;
		}
		sum_x += x;
		sum_y += y;
	}

	mean_x = sum_x / num_elem;
	mean_y = sum_y / num_elem;

	printf("mean_x = %+.15lf\n", mean_x);
	printf("mean_y = %+.15lf\n", mean_y);

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

	ret = create_file_v2(filename);
	if (ret != 0)
	{
		return ret;
	}
	ret = process_file_v2(filename);
	if (ret != 0)
	{
		return ret;
	}

	return 0;
}