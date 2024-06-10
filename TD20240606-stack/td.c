#include "stack.h"
#include <string.h>

int main(int argc, const char *argv[])
{
	list stack;
	char *s = "Ressasser";

	init_stack(&stack);

	for (int i = 0; i < strlen(s);i++) {
		push(&stack, s[i]);
	}

	for (int i = 0; i < strlen(s);i++) {
		element e = pop(&stack);
		printf("%c", e);
	}
	puts("");

	return 0;
}