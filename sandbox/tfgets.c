#include <stdio.h>
#include <string.h>

#define NUM_USABLE_CHAR 8
#define N (NUM_USABLE_CHAR+2) // +1 for \n, +1 for \0

int main(int argc, const char *argv[])
{
	FILE *f = fopen("data/data.txt","r");
	char s[N];

	printf("NUM_USABLE_CHAR=%d\n", NUM_USABLE_CHAR);
	fgets(s, N, f);

	for (int i = 0; i < N;i++)
		printf("%02X ", s[i]);
	puts("");
	//printf("strlen(s)=%ld\n", strlen(s));
	if(strlen(s)==N-1 && s[N-2]!='\n') {
		puts("line too long !");
	}
	else {
		if(!feof(f))
			s[strlen(s) - 1] = 0;
		printf("s=[%s]\n", s);
	}
	return 0;
}