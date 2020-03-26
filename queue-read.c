/*
 * ./parser.c
 * Parses a string and validates every word contained therein.
 * Created: 2020-03-20 20:10
 * Author : Leomar Duran <https://github.com/lduran2>
 * For    : CIS 3207, Spring 2020
 */
#include "parser.h"

/**
 * Parses the string *haystack and validates every word contained
 * therein.
 * @params
 *   *out      : FILE   = file whereto to print validations
 *   *haystack : char   = the string to search
 *   *dict     : FILE   = the dictionary file
 * @returns true on success, false on failure.
 */
void
parse(FILE *out, sbuf_t *log, char *haystack, FILE *dict)
{
	/* whether the state is in the separator class */
	bool in_separator = false;

	/* for creating new words */
	char *offset = haystack;	/* offset within haystack */

	/* loop until end of haystack */
	while (*haystack) {
		/* state: in regular (non-separator) text */
		if (!in_separator) {
			/* if the current string is in the separator */
			/* class, i.e., not a word character */
			if (!is_word_char(*haystack)) {
				/* validate the string so far */
				validate_next_word
					(out, offset, haystack, dict);
				/* update the state */
				in_separator = true;
			} /* end if (in_class(haystack, separators)) */
		} /* end if (!in_separator) */
		/* state: in the separator class */
		else {
			/* if the current string is no longer in the */
			/* separator class */
			if (is_word_char(*haystack)) {
				/* exit the in_separator state */
				in_separator = false;
				/* update the offset */
				offset = haystack;
				/* stay on same character */
				continue;
			} /* end if (is_word_char(*haystack)) */
		} /* end if (in_separator) */

		/* priority logic: continue to next character */
		++haystack;
	} /* end while (*haystack) */

	/* if last character was in a word: */
	if (!in_separator) {
		/* validate the last word */
		validate_next_word(out, offset, haystack, dict);
	}
} /* end parse(char *haystack, int *pargc, char ***pargv) */

/**
 * Validates the string between *offset inclusive and *end exclusive.
 * @params
 *   *out    : FILE = the file to print to
 *   *offset : char  = the beginning of the subtring (inclusive)
 *   *end    : char  = the end of the substring (exclusive)
 */
void
validate_next_word(FILE *out, sbuf_t log, char *offset, char *end, FILE *dict)
{
	int len;	/* length of the new word */
	char *new_word = NULL;	/* the new word */
	const char *result;	/* the result of validation */

	/* calculate and check the length */
	len = end - offset;
	/* if the length is 0, then don't print */
	if (0 == len) return;

	/* copy the new word */
	new_word = malloc(len * sizeof(char));
	strncpy(new_word, offset, len);

	/* validate the new word */
	result = validate(new_word, dict);

	/* print and free the result */
	fprintf(out, "%s %s\n", new_word, result);
	free(new_word);
} /* end validate_next_word
	(FILE *out, char *offset, char *end, FILE *dict)
   */

/**
 * Validates a word against the dictionary.
 * @params
 *   *key  : char = the word to validate
 *   *dict : FILE = dictionary whereagainst to check the word
 * @returns
 *   "OK"         -- if the key is found in the dictionary
 *   "MISSPELLED" -- otherwise
 */
const char*
validate(char *key, FILE *dict)
{
	/* constants to return */
	static const char *OK = "OK";	/* success */
	static const char *MISSPELLED = "MISSPELLED";	/* failture */

	char *dict_word = "";	/* the current word in the dictionary */
	bool equal;	/* whether the words are equal */

	/* restart the dictionary */
	rewind(dict);

	/* search the dictionary */
	while (read_line(dict, &dict_word)) {
		/* check the key against this word */
		equal = is_correctly_spelled(key, dict_word);
		/* dictionary word no longer needed */
		free(dict_word);
		/* if found the key */
		if (equal) {
			/* return success */
			return OK;
		} /* end if (0 == strcmp(key, test)) */
	} /* end while (0 <= fscanf(dict, "%s\n", &test)) */

	/* return failure */
	return MISSPELLED;
} /* end validate(char *word, FILE *dict) */

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

bool
is_correctly_spelled(char *to_test, char *correct)
{
	return (
		/* compare first characters */
		(
			(*to_test == *correct)	/* without capital */
			|| (*to_test == (*correct & '_')) /* with capital */
		)
		/* compare rest of the words */
		&& (0 == strcmp(to_test + 1, correct + 1))
	);
} /* end is_correctly_spelled(char *to_text, char *correct) */

/**
 * Test whether a character is a word character.
 * @params
 *   c : char = character to test
 * @returns whether a character is a word character
 */
bool
is_word_char(char c)
{
	return (((c >= 'a') && (c <= 'z'))	/* lowercase */
		|| ((c >= 'A') && (c <= 'Z'))	/* uppercase */
		|| (c == '\'')	/* apostrophe */
	);
} /* end is_word_char(char c) */

