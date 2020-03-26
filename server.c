#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#define	DEFAULT_DICTIONARY ((char *)"/usr/share/dict/words")
#define	DEFAULT_PORT ((portnum_t)8080)
#define	LOG_NAME ((char *)"server.log")
#define LOG_WRITE_MODE ((char *)"w")

typedef short unsigned portnum_t;

extern int errno;

bool
parse_port(portnum_t *pport, char *str);

int
main(int argc, char **argv)
{
	FILE *dictionary;	/* dictionary with which to spellcheck */
	portnum_t port;	/* port number*/
	FILE *log;	/* the log file */

	/* open the dictionary, defaulting as needed */
	if ((argc <= 1) || (NULL == (dictionary = fopen(argv[1], "r")))) {
		printf("Failed to open dictionary, so using default.\n");
		dictionary = fopen(DEFAULT_DICTIONARY, "r");
	} /* end if ((argc <= 1) || (NULL == fopen(argv[1], "r"))) */

	/* parse the port number, defaulting as needed */
	if ((argc <= 2) || (!parse_port(&port, argv[2]))) {
		port = DEFAULT_PORT;
	} /* end if ((argc <= 2) || (!parse_port(, argv[2]))) */

	/* create the log file */
	log = fopen(LOG_NAME, LOG_WRITE_MODE);

	printf("%d\n", port);

}

bool
parse_port(portnum_t *pport, char *str)
{
	long local_port;	/* local copy of *pport */
	int errsv;	/* error save */

	printf("%s\n", str);

	errno = 0;	/* clear error */
	local_port = strtol(str, (char **)NULL, 10);	/* wrap strtol */
	/* check if error is still clear */
	errsv = errno;
	if (errsv) {
		/* failed */
		return false;
	} /* end if (!errno) */

	/* on success, set the port*/
	*pport = (portnum_t)local_port;
	return true;
} /* end parse_port(portnum_t *port, char *str) */

