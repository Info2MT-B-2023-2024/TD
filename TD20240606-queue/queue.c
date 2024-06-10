#include "queue.h"

error_code init_queue(list *s) {
    return init_list(s);
}

error_code enqueue(list *s, element e) {
    return insert(s, e, 0);
}

element dequeue(list *s) {

    element e = s->e[s->num_elem - 1];
    delete (s, s->num_elem - 1);
    return e;
}
