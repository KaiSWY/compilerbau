/* Project:  COCKTAIL training
 * Descr:    A Recursive Decent Parser for expressions
 * Kind:     REX Scanner specification
 * Author:   Dr. Juergen Vollmer <Juergen.Vollmer@informatik-vollmer.de>
 * $Id: expr.rex,v 1.3 2020/06/14 17:57:03 vollmer Exp $
 */

SCANNER expr_scan

EXPORT {
# include "Position.h"

typedef int tToken;
typedef struct {tPosition Pos; char* Value;} tidentifier;

typedef union {
  tPosition   Position;
  tidentifier identifier;
} expr_scan_tScanAttribute;

# define tok_identifier 1
# define tok_pd         2
}

DEFAULT {
  WritePosition (stderr, expr_scan_Attribute.Position);
  fprintf (stderr, " Illegal character [%c]\n", *expr_scan_TokenPtr);
  exit (1);
}

DEFINE
  digit  = {0-9}       .
  letter = {a-z_A-Z}   .

RULES

/* identifiers */
#STD# letter (letter | digit) * :
	{expr_scan_Attribute.identifier.Value =
			(char*) malloc (expr_scan_TokenLength + 1);
	 expr_scan_GetWord (expr_scan_Attribute.identifier.Value);
	 return tok_identifier;
	}

#STD# "+": {return '+';}
#STD# "*": {return '*';}
#STD# "(": {return '(';}
#STD# ")": {return ')';}
#STD# "->": {return tok_pd;}
#STD# ".": {return '.';}
#STD# "[": {return '[';}
#STD# "]": {return ']';}

#STD# < "--" ANY *  :
        { /* comment up to end of line, nothing to do */
        }

/**********************************************************************/
