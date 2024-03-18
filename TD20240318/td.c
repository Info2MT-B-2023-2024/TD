#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int process_bmp_file(const char *filename)
{
	const unsigned short BMP_SIGNATURE = 0x4D42; // BM
	FILE *f = NULL;
	int ret = 0;
	f = fopen(filename, "rb");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}

	// read the signature
	unsigned short signature = 0;
	ret = fread(&signature, sizeof(unsigned short), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading signature of %s.\n", filename);
		return 1;
	}
	printf("signature=%04X, %c %c ", signature, signature & 0xFF, (signature >> 8) & 0xFF);
	puts("");
	if (signature != BMP_SIGNATURE)
	{
		fprintf(stderr, "error bad signature in %s.\n", filename);
		return 1;
	}

	// read the data offset value
	uint32_t data_offset = 0;
	fseek(f, 10, SEEK_SET);
	ret = fread(&data_offset, sizeof(uint32_t), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading data_offset in %s.\n", filename);
		return 1;
	}
	printf("data_offset=%d\n", data_offset);

	// read the image size
	uint32_t width = 0;
	uint32_t height = 0;
	fseek(f, 4, SEEK_CUR);
	ret = fread(&width, sizeof(uint32_t), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading width in %s.\n", filename);
		return 1;
	}
	ret = fread(&height, sizeof(uint32_t), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading height in %s.\n", filename);
		return 1;
	}
	printf("width=%d\n", width);
	printf("height=%d\n", height);

	// read the pixels size
	uint16_t planes = 0;
	uint16_t bits_per_pixel = 0;
	ret = fread(&planes, sizeof(uint16_t), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading planes in %s.\n", filename);
		return 1;
	}
	ret = fread(&bits_per_pixel, sizeof(uint16_t), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading bits_per_pixel from %s.\n", filename);
		return 1;
	}
	printf("planes=%d\n", planes);
	printf("bits_per_pixel=%d\n", bits_per_pixel);

	unsigned char *img = NULL;
	size_t img_size = width * height * bits_per_pixel / 8 * planes;
	img = (unsigned char *)malloc(img_size * sizeof(unsigned char));
	if (NULL == img)
	{
		fprintf(stderr, "error while allocating memory for %s.\n", filename);
		return 1;
	}
	fseek(f, data_offset, SEEK_SET);
	ret = fread(img, sizeof(unsigned char), img_size, f);
	if (ret != img_size)
	{
		fprintf(stderr, "error while reading data from %s.\n", filename);
		free(img);
		return 1;
	}

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		free(img);
		return 1;
	}

	size_t line = 0;
	size_t column = 0;
	for (line = 0; line < height; line += 1)
	{
		for (column = 0; column < width; column += 1)
		{
			size_t index = (line * width + column) * bits_per_pixel / 8;
			unsigned char r = img[index];
			putchar(r > 127 ? '*' : ' ');
		}
		puts(""); // putchar('\n');
	}
	free(img);

	return 0;
}

int main(int argc, const char *argv[])
{

	const char *filename = "data/smile.bmp";
	int ret = 0;

	ret = process_bmp_file(filename);
	if (ret != 0)
	{
		return ret;
	}

	return 0;
}