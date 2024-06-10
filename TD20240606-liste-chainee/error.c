#include "error.h"
#include <stdio.h>

void display_error(error_code err)
{
	switch (err)
	{
	case NO_ERROR:
		printf("No error\n");
		break;
	case BAD_POSITION:
		printf("ERROR: Bad position\n");
		break;
	case LIST_FULL:
		printf("ERROR: List full\n");
		break;
	default:
		printf("ERROR: Unknown error\n");
		break;
	}
	return;
}
