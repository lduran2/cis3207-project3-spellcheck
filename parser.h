/*
 * ./parser.h
 * Functions for parsing a string and validating every word contained
 * therein.
 * Created: 2020-03-20 22:08
 * Author : Leomar Duran <https://github.com/lduran2>
 * For    : CIS 3207, Spring 2020
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifndef LDURAN2_SPELLCHECK_PARSER_H
#define LDURAN2_SPELLCHECK_PARSER_H

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
parse(FILE *out, char *haystack, FILE *dict);

/**
 * Validates the string between *offset inclusive and *end exclusive.
 * @params
 *   *out    : FILE  = the file to print to
 *   *offset : char  = the beginning of the subtring (inclusive)
 *   *end    : char  = the end of the substring (exclusive)
 */
void
validate_next_word(FILE *out, char *offset, char *end, FILE *dict);

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
validate(char *key, FILE *dict);

/**
 * Reads a line from the file.
 * @params
 *   *in    : FILE  = file wherefrom to read
 *   *pline : char* = pointer to the string read
 * @returns whether a line was read
 */
bool
read_line(FILE *in, char **pline);

/**
 * Test whether a character is a word character.
 * @params
 *   c : char = character to test
 * @returns whether a character is a word character
 */
bool
is_word_char(char c);

#endif /* #ifndef LDURAN2_SPELLCHECK_PARSER_H */

