#pragma once

typedef enum
{
	NO_ERROR,
	BAD_POSITION,
	LIST_FULL,
	ALLOCATION_ERROR,
} error_code;

typedef struct
{
	error_code code;
	char *message;
} error;

void display_error(error_code err);

