#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int
main(int argc, char** argv)
{
	bool usestdin = argc < 2;
	putchar('(');
	if (usestdin) {
		char* str;
		int idx = 0;
		char* buf[BUFSIZ];
		while (fscanf(stdin, "%s", str) != EOF)
			buf[idx++] = str;
		
		unsigned len = idx;
		for (int i = 0; i < len; i++) {
			printf("%s", buf[i]);
			if (i < len-1)
				putchar(' ');
		}
	} else {
		for (int i = 1; i < argc; i++) {
			printf("%s", argv[i]);
			if (i < argc - 1)
				putchar(' ');
		}
	}
	putchar(')');
	putchar('\n');
	return 0;
}
