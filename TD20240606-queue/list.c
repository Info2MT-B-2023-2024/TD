#include "list.h"
#include <stdlib.h>
#include <string.h>

error_code init_list(list *l)
{
    l->e = (element *)realloc(NULL, (INITIAL_CAPACITY) * sizeof(element));
    if (NULL == l->e)
        return ERR_ALLOC;
    printf("init_list: l->e=%p\n", l->e);
    l->capacity = INITIAL_CAPACITY;
    l->num_elem = 0;
    return NO_ERROR;
}

void display_list(const list l)
{
    for (size_t index = 0; index < l.num_elem; index++)
    {
        printf("%cx",
               l.e[index]);
    }
}

bool list_is_full(const list l)
{
    return (l.capacity == l.num_elem);
}

bool list_is_empty(const list l)
{
    return (0 == l.num_elem);
}

error_code insert(list *l, const element e, const size_t position)
{
    if (list_is_full(*l))
    {
        printf("updating capacity...\n");
        element *tmp = (element *)realloc(l->e, (l->capacity + UPDATE_CAPACITY) * sizeof(element));
        if (NULL == tmp)
            return ERR_LIST_FULL;
        l->e = tmp;
        l->capacity += UPDATE_CAPACITY;
    }

    if (position > l->num_elem)
        return ERR_BAD_POSITION;

    for (int i = l->num_elem; i > position; i--)
    {
        l->e[i] = l->e[i - 1];
    }
    l->e[position] = e;
    l->num_elem++;
    return NO_ERROR;
}

error_code delete(list *l, const size_t position)
{

    if (position >= l->num_elem)
        return ERR_BAD_POSITION;

    for (int i = position + 1; i < l->num_elem; i++)
    {
        l->e[i - 1] = l->e[i];
    }
    l->num_elem--;
    return NO_ERROR;
}

int search(const list l, const element e)
{
    for (size_t index = 0; index < l.num_elem; index++)
    {
        // compare l.e[index] with e using memcmp
        if (0 == memcmp(&(l.e[index]), &e, sizeof(element)))
        {
            return index;
        }
    }
    return -1;
}