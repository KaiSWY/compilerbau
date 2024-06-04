/*
 * Project:     Course: Introduction into Programming with C
 * Descr:       Common Definitions and general routines
 * Author:      Prof. Dr. Jürgen Vollmer <juergen.vollmer@dhbw-karlsruhe.de>
 * $Id: common.h,v 1.12 2022/04/30 09:37:32 vollmer Exp $
 * -*- coding: latin-1 -*-
 */

# ifndef JV_COMMON_H
# define JV_COMMON_H

#include <assert.h>
/* compile with
 * enableing assert()-macro:    -U NDEBUG    that's the default
 * disabeling assert()-macro:   -D NEDBUG
 */

#include <stdlib.h>
# include <stdio.h>


/* Printing debug information
 * compile with   -D DEBUG   stuff is shown
 * compile withb  -U DEBUG   stuff is hnot shown, default
 */
# ifdef  DEBUG
# define DPRINTF printf
# else
# define DPRINTF  if(0) printf
# endif

/* a datatype for boolean values */
typedef enum {
  false = 0,
  true
} bool;

extern bool VERBOSE;
#define VPRINTF if (VERBOSE) printf

/* based on argv[0] passed to main() */
extern void init_CMD(const char *argv0);  /* initialize those variables */
extern char* CMD;      /* name of the program */
extern char* CMD_DIR;  /* directory containing the exceutable, when called  */

/* the following functions must be defined in e.g. the file containing main() */
/* print the usage / help message of the program */
extern void usage(void);

/* handle the commandline options and arguments, passed to main()
 * short options have the form  -X   where X is a letter or digit
 * arguments don'st start with a - and follow the options.
 * see getopt()  and getop_long()
 * handleArgs() returns
 * - a NULL-pointer terminated array of char-pointers to the arguments.
 * or
 * NULL if no further argument isgiven or they could be ignored
 */
extern char **handleArgs(int argc, char* argv[]);

# endif

/*****************************************************************************************/
