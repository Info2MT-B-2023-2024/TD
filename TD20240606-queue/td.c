#include "queue.h"
#include <string.h>

int main(int argc, const char *argv[])
{
	list queue;
	char *s = "Il fait beau et chaud";

	init_queue(&queue);

	for (int i = 0; i < strlen(s);i++) {
		enqueue(&queue, s[i]);
	}

	for (int i = 0; i < strlen(s);i++) {
		element e = dequeue(&queue);
		printf("%c", e);
	}
	puts("");

	return 0;
}