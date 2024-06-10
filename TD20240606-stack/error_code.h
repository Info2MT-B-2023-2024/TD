#pragma once

typedef enum
{
    NO_ERROR=0,
    ERR_ALLOC,
    ERR_LIST_EMPTY,
    ERR_LIST_FULL,
    ERR_BAD_POSITION,
    ELEMENT_NOT_FOUND
} error_code;