#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	POINT2D = 0,
	COLOR,
	END
} data_type;

char *data_type_name[END] = {
	"POINT 2D",
	"COLOR"};

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
	header h;
	data *d; // pointer to dynamic data area
} packet;

data *init_packet(const data_type type, const size_t qty, const uint8_t checksum, packet *p)
{
	if (NULL == p)
		return NULL;

	p->h.type = type;
	p->h.qty = qty;
	p->h.checksum = checksum;

	p->d = (data *)malloc(p->h.qty * sizeof(data));
	return p->d;
}

void display_packet(const packet p)
{
	switch (p.h.type)
	{
	case POINT2D:
		printf("Type: POINT2D\n");
		break;
	case COLOR:
		printf("Type: COLOR\n");
		break;
	default:
		puts("Unknown packet type.");
		return;
		break;
	}
	printf("Type: %s\n", data_type_name[p.h.type]);
	printf("Qty:  %zu\n", p.h.qty);

	size_t index = 0;
	for (index = 0; index < p.h.qty; index++)
	{
		switch (p.h.type)
		{
		case POINT2D:
			printf("element %zu: x=%+6.3lf, y=%+6.3lf\n",
				   index, p.d[index].p.x, p.d[index].p.y);
			break;
		case COLOR:
			printf("element %zu: r=%3d, g=%3d, b=%3d\n",
				   index, p.d[index].c.r, p.d[index].c.g, p.d[index].c.b);
			break;
		default:
			puts("Unknown packet type.");
			break;
		}
	}
}

void send(const packet p, char *buff)
{
	memcpy(buff, &(p.h), sizeof(header));
	buff += sizeof(header);
	memcpy(buff, p.d, p.h.qty * sizeof(data));
}

void receive(char *buff, packet *p)
{
	memcpy(&(p->h), buff, sizeof(header));
	buff += sizeof(header);
	data *pdata = (data *)malloc(p->h.qty * sizeof(data));
	if (NULL == pdata)
	{
		printf("Error allocation pdata.");
		return;
	}

	p->d = pdata; // (*p).d = pdata;
	memcpy(p->d, buff, p->h.qty * sizeof(data));
}

int main(void)
{
	packet p1;
	packet p2;
	color red = {255, 0, 0};
	color green = {0, 255, 0};
	color blue = {0, 0, 255};

	if (NULL == init_packet(COLOR, 3, 0, &p1))
	{
		printf("Error allocation data for p1.");
		return 1;
	}

	p1.d[0].c = red; // =  struct => copy all fields
	p1.d[1].c = green;
	p1.d[2].c = blue;

	display_packet(p1);

	char *buff = (char *)malloc(p1.h.qty * sizeof(data) + sizeof(header));
	if (NULL == buff)
	{
		printf("Error allocation buffer.");
		return 1;
	}

	send(p1, buff);
	receive(buff, &p2);
	display_packet(p2);
}