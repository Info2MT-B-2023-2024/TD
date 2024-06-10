#pragma once
#include "error_code.h"
#include "list.h"

error_code init_stack(list *s);
error_code push(list *s, element e);
element pop(list *s);

