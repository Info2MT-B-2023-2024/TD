#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "error_code.h"

#define INITIAL_CAPACITY 5
#define UPDATE_CAPACITY 4


typedef char element;

typedef struct {

    element *e;
    size_t capacity;
    size_t num_elem;

} list;

error_code init_list(list *l);
void display_list(const list l);
bool list_is_full(const list l);
error_code insert(list *l, const element e, const size_t position);
error_code delete(list *l, const size_t position);
int search(const list l, const element e);