#include <stdio.h>

void
upper(char* letter)
{
	char up = (*letter) - ' ';
	*letter = up;
}

int
main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	for (int i = 1; i < argc; i++) {
		upper(argv[i]);
		printf("%s ", argv[i]);
	}
	putchar('\n');

	return 0;
}
