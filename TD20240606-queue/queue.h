#pragma once
#include "error_code.h"
#include "list.h"

error_code init_queue(list *s);
error_code enqueue(list *s, element e);
element dequeue(list *s);

