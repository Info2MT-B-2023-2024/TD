#include "stack.h"

error_code init_stack(list *s) {
    return init_list(s);
}

error_code push(list *s, element e) {
    size_t pos = s->num_elem;
    return insert(s, e, pos);
}

element pop(list *s) {

    element e = s->e[s->num_elem - 1];
    delete (s, s->num_elem - 1);
    return e;
}
