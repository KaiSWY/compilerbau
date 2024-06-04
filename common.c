/*
 * Project:     Course: Introduction into Programming with C
 * Descr:       Common Definitions and general routines,
 * Note:        this file should be included once in the file containing main()
 * Author:      Prof. Dr. Jürgen Vollmer <juergen.vollmer@dhbw-karlsruhe.de>
 * $Id: common.c,v 1.5 2019/06/12 15:10:31 vollmer Exp $
 * -*- coding: latin-1 -*-
 */

#include <string.h>
#include <libgen.h>
# include "common.h"

bool VERBOSE = false;

char* CMD;
char* CMD_DIR;

void init_CMD(const char *argv0)
{
  /* obey notes given in man(3) of basename() and dirname() concerning allocation of memeory */
  static char ARGV0[256];
  strncpy (ARGV0, argv0, 255);
  ARGV0[255] = '\0';
  CMD     = basename (ARGV0);
  CMD_DIR = dirname  (ARGV0);

  DPRINTF ("CMD     =[%s]\n", CMD);
  DPRINTF ("CMD_DIR =[%s]\n", CMD_DIR);
} /* init_CMD() */


/*****************************************************************************************/
