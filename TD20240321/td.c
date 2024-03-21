#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
	uint16_t type;
	uint32_t size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
} bmp_header;

typedef struct
{
	uint32_t size;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bits_per_pixel;
	uint32_t compression;
	uint32_t image_size;
	int32_t x_pixels_per_meter;
	int32_t y_pixels_per_meter;
	uint32_t colors_used;
	uint32_t colors_important;
} bmp_info_header;

typedef struct
{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} pixel_color;
#pragma pack(pop)

int process_bmp_file(const char *filename)
{
	bmp_header header;
	bmp_info_header infoHeader;

	printf("sizeof(bmp_header)=%ld\n", sizeof(bmp_header));
	printf("sizeof(bmp_info_header)=%ld\n", sizeof(bmp_info_header));

	const unsigned short BMP_SIGNATURE = 0x4D42; // BM
	FILE *f = NULL;
	int ret = 0;
	f = fopen(filename, "rb");
	if (NULL == f)
	{
		fprintf(stderr, "error while opening %s.\n", filename);
		return 1;
	}
	ret = fread(&header, sizeof(bmp_header), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading header of %s.\n", filename);
		return 1;
	}
	if (header.type != BMP_SIGNATURE)
	{
		fprintf(stderr, "error bad signature in %s.\n", filename);
		return 1;
	}
	printf("signature=%04X, %c %c\n", header.type, header.type & 0xFF, (header.type >> 8) & 0xFF);
	printf("size=%d\n", header.size);
	printf("offset=%d\n", header.offset);

	ret = fread(&infoHeader, sizeof(bmp_info_header), 1, f);
	if (ret != 1)
	{
		fprintf(stderr, "error while reading infoHeader of %s.\n", filename);
		return 1;
	}
	printf("size=%d\n", infoHeader.size);
	printf("width=%d\n", infoHeader.width);
	printf("height=%d\n", infoHeader.height);
	printf("planes=%d\n", infoHeader.planes);
	printf("bits_per_pixel=%d\n", infoHeader.bits_per_pixel);
	printf("compression=%d\n", infoHeader.compression);

	pixel_color *img = NULL;
	size_t img_size = infoHeader.width * infoHeader.height;
	img = (pixel_color *)malloc(img_size * sizeof(pixel_color));
	if (NULL == img)
	{
		fprintf(stderr, "error while allocating memory for %s.\n", filename);
		return 1;
	}
	fseek(f, header.offset, SEEK_SET);
	ret = fread(img, sizeof(pixel_color), img_size, f);
	if (ret != img_size)
	{
		fprintf(stderr, "error while reading data from %s.\n", filename);
		free(img);
		return 1;
	}

	size_t line = 0;
	size_t column = 0;
	for (line = 0; line < infoHeader.height; line += 1)
	{
		for (column = 0; column < infoHeader.width; column += 1)
		{
			size_t index = (line * infoHeader.width + column);
			if (img[index].red > 128 && img[index].green <= 128 && img[index].blue <= 128)
			{
				printf("\e[1;41m "); // RED
			}
			else if (img[index].red <= 128 && img[index].green > 128 && img[index].blue <= 128)
			{
				printf("\e[1;42m "); // GREEN
			}
			else if (img[index].red <= 128 && img[index].green <= 128 && img[index].blue > 128)
			{
				printf("\e[1;44m "); // BLUE
			}
			else if (img[index].red > 127 && img[index].green > 128 && img[index].blue > 128)
			{
				printf("\e[1;47m "); // WHITE
			}
			else
			{
				printf("\e[1;40m "); // BLACK
			}
		}
		printf("\e[0m\n"); // WHITE 
	}

	if (fclose(f) != 0)
	{
		fprintf(stderr, "error while closing %s.\n", filename);
		free(img);
		return 1;
	}
	free(img);

	return 0;
}

int main(int argc, const char *argv[])
{
	const char *filename = "data/smile2.bmp";
	int ret = 0;

	ret = process_bmp_file(filename);
	if (ret != 0)
	{
		return ret;
	}
	return 0;
}



