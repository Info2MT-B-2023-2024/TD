#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	POINT2D = 1,
	COLOR
} data_type;

typedef struct
{
	double x; /**< horizontal */
	double y; /**< vertical */
} point2D;

/**
 *
 */
typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color;

typedef struct
{
	data_type type;
	size_t qty;
	uint8_t checksum;
} header;

typedef union
{
	point2D p;
	color c;
} data;

typedef struct
{
	header h; /*!< the header */
	data d;	  /*!< the payload */
} packet;

void display_packet(const packet p)
{
	data the_data = p.d;
	switch (p.h.type)
	{
	case POINT2D:
		printf("Point2D: x=%+6.3lf, y=%+6.3lf\n",
			   the_data.p.x, the_data.p.y);
		break;
	case COLOR:
		printf("Color: r=%3d, g=%3d, b=%3d\n",
			   the_data.c.r, the_data.c.g, the_data.c.b);
		break;
	default:
		puts("Unkwon packet type.");
		break;
	}
}

void send(const packet p, char *buff) {
	size_t n = sizeof(header) + p.h.qty * sizeof(data);
	memcpy(buff, &p, n);
}
void receive(char *buff, packet *p) {
	// TODO: write the function :)
}

int main(void)
{

	packet p1;
	packet p2;
	char *buffer = NULL;
	p1.h.type = POINT2D;
	p1.h.qty = 1;
	p1.h.checksum = 0x00;

	p1.d.p.x = 10.;
	p1.d.p.y = 15.;

	buffer = (char *)malloc(sizeof(header) + p1.h.qty * sizeof(data));
	if (NULL == buffer)
	{
		printf("Error, unable to allocate memory for the buffer.");
		return 1;
	}

	display_packet(p1);
	send(p1, buffer);
	receive(buffer, &p2);
	display_packet(p2);

	return 0;
}

/*
typedef struct {
	double r;
	double i;
} complex;

complex c1= {.r=0., .i=4.};

struct complex {
	double r;
	double i;
};

struct complex c1;

typedef struct complex {
	double r;
	double i;
} complex;

complex c1;
*/