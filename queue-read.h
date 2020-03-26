/*
 * ./queue_read.h
 * Defines a function to reduce every line of a file into an object.
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
 * Function for reducing objects.
 * @params
 *   *reducer : void = the object that reduces
 *   *obj     : void = each object to reduce
 */
typedef void (*reduce_f)(void *reducer, void *obj);

/**
 * Function for mapping strings to object.
 * @params
 *   *str : char = the string to map
 * @returns the output of the mapping.
 */
typedef void *(*map_f)(char *str);

/**
 * Consumes each line from a file.
 * @params
 *   *reducer : void     = the object that reduces from the file
 *   reduce   : reduce_f = the function for reducing each mapped line
 *   map      : map_f    = the function for mapping each line
 *   *file    : FILE     = the file wherefrom to reduce
 */
void
each_line(void *reducer, reduce_f reduce, map_f map, FILE *file);

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

