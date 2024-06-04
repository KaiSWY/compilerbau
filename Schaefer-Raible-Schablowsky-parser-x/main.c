/* Project:  COCKTAIL training
 * Descr:    LR parser for an expression language
 * Kind:     C-main program
 * Author:   Dr. Juergen Vollmer <Juergen.Vollmer@informatik-vollmer.de>
 * $Id: main.c,v 1.2 2007/06/01 15:41:25 vollmer Exp $
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "Position.h"
# include "Errors.h"
# include "x_scan.h"
# include "x_pars.h"

int main (int argc, char *argv[])
{
   int errors = 0;
   if (argc == 2) {
     if (strcmp (argv[1], "-h") == 0) {
       fprintf (stderr,
		"usage: %s [-h] [file]\n"
		"  expression LR based parser, reads `file' or stdin\n"
		"  -h: Help\n", argv[0]);
       exit (0);
     }

     x_scan_Attribute.Position.FileName = MakeIdent1 (argv[1]);
     x_scan_BeginFile (argv[1]);
     /* Read from file argv[1].
      * If this routine is not called, stdin is read.
      */
   }

   errors = x_pars();  /* the parser */

   printf ("parser returned: %d number of errors: %d\n", errors, GetCount(xxError));

   return (errors == 0) ? 0 : 1;
}
