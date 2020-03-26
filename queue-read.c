/*
 * ./queue-read.c
 * Provides a function to consume every line of a file into an object.
 * Created: 2020-03-25 20:42
 * Author : Leomar Duran <https://github.com/lduran2>
 * For    : CIS 3207, Spring 2020
 */
#include "queue-read.h"

/**
 * Consumes each line from a file.
 * @params
 *   consume   : consume_f = the function for consuming each line
 *   *consumer : void      = the object that consumes from the file
 *   *file     : FILE      = the file wherefrom to consume
 */
void
each_line(consume_f consume, void *consumer, FILE *file)
{
	char *line = "";	/* the current word in the dictionary */

	/* for each line in the file */
	while (read_line(file, &line)) {
		/* push the line onto the queue */
		consume(consumer, line);
	} /* end while (read_line(file, )) */
} /* end each_line(consume_f consume, void *consumer, FILE *dict) */

/**
 * Reads a line from the file.
 * @params
 *   *in    : FILE  = file wherefrom to read
 *   *pline : char* = pointer to the string read
 * @returns whether a line was read
 */
bool
read_line(FILE *in, char **pline)
{
	char *line;	/* local read */
	char *raw_line = NULL;	/* line read in, raw from getline */
	size_t n = 0;	/* line length */

	/* accept a new raw line */
	getline(&raw_line, &n, in);

	/* get the length removing the line feed '\n' */
	n = (strlen(raw_line) - 1);
	/* return false if no characters were read */
	if ((long signed)n <= 0) {
		return false;
	} /* end read_line(FILE *in, char **pline) if (n <= 0) */

	/* properly terminate the line */
	line = malloc((n + 1) * sizeof(char));
	strncpy(line, raw_line, n);
	strcat(line, "\0");

	/* stores the line */
	*pline = line;
	/* return that a string was read */
	return true;
} /* end read_line(FILE *in, char **pline) */

