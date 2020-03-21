/*
 * ./test-parser.c
 * Tests the parsing method.
 * Created: 2020-03-20 20:22
 * Author : Leomar Duran <https://github.com/lduran2>
 * For    : CIS 3207, Spring 2020
 */
#include "parser.h"
#define DEFAULT_DICTIONARY "/usr/share/dict/words"

int
main(int argc, int argv)
{
	/* messages to test */
	char *messages[] = {
		"Hello, world! Hello, mundo! end",
		"Hello, world! Hello, mundo!",
		"Hello, world! Hello, mundo!!!",
		NULL
	};
	char **pmessage = messages;	/* pointer to message */

	FILE *dict;	/* default dictionary */

	/* open the dictionary and make sure it exists */
	if (NULL == (dict = fopen(DEFAULT_DICTIONARY, "r"))) {
		fprintf(stderr, 
			"Default dictionary %s file not found.",
			DEFAULT_DICTIONARY);
		return 1;
	} /* end if (NULL == (dict = fopen(DEFAULT_DICTIONARY))) */

	/* test each message */
	for (; *pmessage; ++pmessage) {
		printf("%s\n", *pmessage);
		parse(stdout, *pmessage, dict);
		printf("\n");
	}

	return 0;
}
