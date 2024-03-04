#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{

	const char *filename = "data/x.bin";
	FILE *f = NULL;
	double x = 3.1415;
	int num_elem = 1;
	unsigned char *p = (unsigned char *)&x;
	size_t i = 0;

	printf("&x = %p\n", (void *)&x);
	printf("x = %+.4lf\n", x);
	for (i = 0; i < sizeof(double); i++)
	{
		printf("%02x ",  *(p + i)); // or p[i]
	}
	puts("");

	f = fopen(filename, "wb");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}
	if (num_elem != fwrite(&x, sizeof(double), num_elem, f))
	{
		fprintf(stderr, "error while write to %s.\n", filename);
		return 1;
	}
	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		return 1;
	}
	// dump in hex format of the content of the binary file:     od -t x1 data/double.bin

	return 0;
}