#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static void
usage(char* argv0)
{
	fprintf(stderr, "Usage: %s <filename>\n", argv0);
}

int
main(int argc, char** argv)
{
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	char* filename = argv[1];
	int acc = access(filename, F_OK);
	if (acc < 0) {
		fprintf(stderr, "Error accessing file: %s\n",
				strerror(errno));
		return 1;
	}

	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening file: %s\n",
				strerror(-fd));
		return 1;
	}

	struct stat statbuf;
	int rc = fstat(fd, &statbuf);
	if (rc < 0) {
		fprintf(stderr, "Error stat()'ing file: %s\n",
				strerror(errno));
		return 1;
	}
	char* errstr = NULL;
	switch ((statbuf.st_mode & S_IFMT)) {
	case S_IFSOCK:
		errstr = "socket";
		break;
	case S_IFLNK:
		errstr = "symbolic link";
		break;
	case S_IFBLK:
		errstr = "block device";
		break;
	case S_IFDIR:
		errstr = "directory";
		break;
	case S_IFCHR:
		errstr = "character device";
		break;
	case S_IFIFO:
		errstr = "FIFO";
		break;
	default:
		errstr = NULL;
		break;
	}
	if (errstr != NULL) {
		fprintf(stderr, "Error: %s is a %s\n",
				argv[1], errstr);
		return 1;
	}

	char buf[statbuf.st_size];
	ssize_t count = read(fd, buf, sizeof(buf));
	if (count < 0) {
		fprintf(stderr, "%s: Error reading file: %s\n",
				argv[0], strerror(-count));
		return 1;
	}

	ssize_t written = write(STDOUT_FILENO, buf, count);
	if (written < 0) {
		fprintf(stderr, "%s: Error writing to stdout: %s\n",
				argv[0], strerror(-written));
		return 1;
	}

	return 0;

}
