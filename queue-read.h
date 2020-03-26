/*
 * ./parser.h
 * Defines a function to consume every line of a file into an object.
 * Created: 2020-03-20 22:08
 * Author : Leomar Duran <https://github.com/lduran2>
 * For    : CIS 3207, Spring 2020
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifndef LDURAN2_SPELLCHECK_QUEUE_READ_H
#define LDURAN2_SPELLCHECK_QUEUE_READ_H

/**
 * Function for consuming from a file.
 * @params
 *   *consumer : void = the object that consumes the strings
 *   *str      : char = each string to consume
 */
typedef void (*consume_f)(void *consumer, char *str);

/**
 * Consumes each line from a file.
 * @params
 *   consume   : consume_f = the function for consuming each line
 *   *consumer : void      = the object that consumes from the file
 *   *file     : FILE      = the file wherefrom to consume
 */
void
each_line(consume_f consume, void *consumer, FILE *file);

/**
 * Reads a line from the file.
 * @params
 *   *in    : FILE  = file wherefrom to read
 *   *pline : char* = pointer to the string read
 * @returns whether a line was read
 */
bool
read_line(FILE *in, char **pline);

#endif /* #ifndef LDURAN2_SPELLCHECK_QUEUE_READ_H */

