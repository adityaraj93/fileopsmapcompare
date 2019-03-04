#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "manager.h"


/* Take two files, FILE1 & FILE2, copy from from FILE1 to FILE2.
   Measure the time taken to do the whole process.

   Employs two ways of copying:
   1. do fopen, read and write.
   2. do mmap, then do memcpy().
*/

static void usage(const char *progname) {
	printf("Usage: %s mmap|file <filename1> <filename2>\n", progname);
}

int main(int argc, char *argv[]) {
	enum op_mode opmode;

	if (argc != 4) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "map") == 0) {
		opmode = OP_MD_MMAP;
	}
	else if(strcmp(argv[1], "file") == 0) {
		printf("Using file.\n");
		opmode = OP_MD_FILEOP;
	}
	else {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if (manage(opmode, argv[2], argv[3]) != 0)
		exit(EXIT_FAILURE);

	return 0;
}
