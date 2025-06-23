/**
 * @brief Assienment 2 - Writer
 *
 * One difference from the write.sh instructions in Assignment 1:  You do
 * not need to make your "writer" utility create directories which do not
 * exist.  You can assume the directory is created by the caller.
 *
 * Setup syslog logging for your utility using the LOG_USER facility.
 *
 * Use the syslog capability to write a message “Writing <string> to <file>”
 * where <string> is the text string written to file (second argument) and
 * <file> is the file created by the script.  This should be written with
 * LOG_DEBUG level.
 *
 * Use the syslog capability to log any unexpected errors with LOG_ERR level.
 */
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS;
	FILE *fd = NULL;
	size_t bytes = 0;
	size_t sizeChar = sizeof(*argv[2]);
	size_t nmemb = strlen(argv[2]);

	if (3 != argc)
	{
		fprintf(stderr, "USAGE: %s <FILENAME> <STRING>\n", argv[0]);
		return EXIT_FAILURE;
	}

	openlog(argv[0], LOG_CONS, LOG_USER);

	fd = fopen(argv[1], "w");
	if (NULL == fd)
	{
		syslog(LOG_ERR, "Unable to open file: %s\n", argv[1]);
		ret = EXIT_FAILURE;
		goto MAIN_EXIT_NOW;
	}

	syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);

	bytes = fwrite(argv[2], sizeChar, nmemb, fd);
	if (bytes != (sizeChar * nmemb))
	{
		syslog(LOG_ERR, "Write unsuccessful: %s\n", argv[1]);
		ret = EXIT_FAILURE;
	}

MAIN_EXIT_NOW:
	if (NULL != fd)
	{
		fclose(fd);
		fd = NULL;
	}

	closelog();
	return ret;
}