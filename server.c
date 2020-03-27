#include "linkedlist.h"
#include "queue-read.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

/* default dictionary for spell checking */
#define	DEFAULT_DICTIONARY "/usr/share/dict/words"
/* default port whereto, to listen */
#define	DEFAULT_PORT ((portnum_t)8080)
/* name of the log file */
#define	LOG_NAME "server.log"
/* writing mode for log file */
#define	LOG_WRITE_MODE "w"
/* number of worker threads */
#define	NUM_WORKERS ((size_t)8)

/* for parsing the port */
#define	DECIMAL (10)

/* type for port numbers */
typedef short unsigned portnum_t;

/* error number for parsing integers */
extern int errno;

bool
parse_port(portnum_t *pport, char *str);

int
main(int argc, char **argv)
{
	FILE *fdict;	/* file of dictionary with which to spellcheck */
	portnum_t port;	/* port number*/
	FILE *log;	/* the log file */

	Queue *qdict;	/* queue containing the dictionary */
	Node *ldict;	/* list containing the dictionary */

	/* open the dictionary, defaulting as needed */
	if ((argc <= 1) || (NULL == (fdict = fopen(argv[1], "r")))) {
		fdict = fopen(DEFAULT_DICTIONARY, "r");
	} /* end if ((argc <= 1) || (NULL == fopen(argv[1], "r"))) */

	/* parse the port number, defaulting as needed */
	if ((argc <= 2) || (!parse_port(&port, argv[2]))) {
		port = DEFAULT_PORT;
	} /* end if ((argc <= 2) || (!parse_port(, argv[2]))) */

	/* create the log file */
	log = fopen(LOG_NAME, LOG_WRITE_MODE);

	/* create a queue */
	qdict = queue_new();
	/* read the dictionary into it */
	each_line(qdict, (reduce_f)queue_enqueue, (map_f)node_new, fdict);
	/* convert to a list */
	ldict = qdict->phead->next;
	
	printf("%lu\n", queue_length(qdict));

}

/**
 * Parses the port number from the specified string.
 * @params
 *   *pport : portnum_t = pointer wherein to store the port number
 *   *str   : char      = string containing the port number
 */
bool
parse_port(portnum_t *pport, char *str)
{
	long local_port;	/* local copy of *pport */
	int errsv;	/* error save */

	printf("%s\n", str);

	errno = 0;	/* clear error */
	/* wrap strtol */
	local_port = strtol(str, (char **)NULL, DECIMAL);
	/* check if error is still clear */
	errsv = errno;
	if (errsv) {
		/* failed */
		return false;
	} /* end if (!errno) */

	/* on success, set the port*/
	*pport = (portnum_t)local_port;
	return true;
} /* end parse_port(portnum_t *pport, char *str) */

