#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

int
main(int argc, char** argv)
{
	if (argc > 3) {
		fprintf(stderr, "Error: %s can only be used on one file at a time\n", argv[0]);
		return 1;
	}
 
	char* filename = "";
	if (argc < 2)
		filename = "/dev/stdin";
	else
		filename = argv[1];

	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "%s: Error opening %s: %s\n",
				argv[0], filename, strerror(-errno));
		return 1;
	}

	char buf[BUFSIZ];
	ssize_t nbytes = read(fd, buf, BUFSIZ); 
	if (nbytes < 0) {
		fprintf(stderr, "Error reading %s: %s\n",
				filename, strerror(-errno));
		return 1;
	}

	size_t len = nbytes / sizeof(buf[0]);
	for (int i = 0; i < len; i++) {
		char current = buf[i];
		putchar(tolower(current));
	}

	close(fd);

	return 0;
}
