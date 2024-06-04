/* Project:  COCKTAIL training
 * Descr:    A recursive Decent Parser for expressions
 * Kind:     The parser (solution)
 * Author:   Dr. Juergen Vollmer <juergen.vollmer@informatik-vollmer.de>
 * $Id: parser.c.in,v 1.5 2017/11/22 10:15:01 vollmer Exp $
 */

# include <stdlib.h>
# include "expr_scan.h"
# include "parser.h"
# include "Errors.h"
      	/* contains: `Message', `MessageI', `xxFatal', `xxError' */

tToken CurToken;

/*****************************************************************************
 * helpers
 *****************************************************************************/

/* Debugging:  if the C-compiler is called with `-DDEBUG',
 *             some output will be generated
 */
# ifdef DEBUG
# define DEBUG_show(msg) printf ("%-5s cur = `%s'\n", msg, token2string (CurToken));
# else
# define DEBUG_show(msg)  /* no output */
# endif

static const char* token2string (tToken token)
/* maps token-code to token textual representation */
{
  switch (token) {
  case '+':
    return "+";
  case '*':
    return "*";
  case '(':
    return "(";
  case ')':
    return ")";
  case tok_identifier:
    return "identifier";
  case tok_pd:
    return "->";
  case '.':
    return ".";
  case '[':
    return "[";
  case ']':
    return "]";
  case expr_scan_EofToken:
    return "EOF";
  default:
    /* this should never happen */
    MessageI ("FATAL ERROR: unknown token", xxFatal,
	      expr_scan_Attribute.Position, xxInteger, (char*) &token);
    abort(); /* aborts the program */
  }
}

/******************************************************************************/

bool match (tToken token)
/* Instead of writing for each token 't' a function 'f_t()', we use
 * 'match (t)'.
 */
{
  DEBUG_show ("MATCH");
# ifdef DEBUG
  printf ("      cur = `%s' expected = `%s'\n", token2string(CurToken), token2string (token));
# endif
  if (CurToken == token) {
    if (CurToken != expr_scan_EofToken) CurToken = expr_scan_GetToken();
    DEBUG_show ("  new");
    return true;
  } else {
    char msg[255];
    sprintf (msg, "Syntax Error: found: `%s' expected: `%s'",
	     token2string (CurToken), token2string (token));
    Message (msg, xxError, expr_scan_Attribute.Position);
    return false;  /* Syntax Error */
  }
}

/*****************************************************************************
 * First-Follow-set Tests
 * 1)  E  ::= T E1         FIRST (T E1      FOLLOW (E))  = { ( id        }
 * 2)  E1 ::= + T E1       FIRST (+ T E1    FOLLOW (E1)) = { +           }
 * 3)  E1 ::= epsilon      FIRST (epsilon   FOLLOW (E1)) = { eof ) ]     }
 * 4)  T  ::= F T1         FIRST (F T1      FOLLOW (T))  = { ( id        }
 * 5)  T1 ::= * F T1       FIRST (* F T1    FOLLOW (T1)) = { *           }
 * 6)  T1 ::= epsilon      FIRST (epsilon   FOLLOW (T1)) = { eof ) + ]   }
 * 7)  F  ::= ( E )        FIRST ( ( E )    FOLLOW (F))  = { (           }
 * 8)  F  ::= id           FIRST (id        FOLLOW (F))  = { id          }
 * 9)  D  ::= id D1        FIRST (id D1     FOLLOW (D))  = { id          }
 *10) D1 ::= . id D1       FIRST (. id D1   FOLLOW (D1)) = { .           }
 *11) D1 ::= [ E ] D1      FIRST ([ E ] D1  FOLLOW (D1)) = { [           }
 *12) D1 ::= -> id D1      FIRST (-> id D1  FOLLOW (D1)) = { ->          }
 *13) D1 ::= epsilon       FIRST (epsilon   FOLLOW (D1)) = { * + ) ] eof }
 *
 * The function 'FirstFollow_i ()' returns true, if and only if 'CurToken'
 * is element of the appropriate set.
 *
 *   eof   <==> expr_scan_EofToken
 *   id    <==> tok_identifier
 ******************************************************************************/

static bool FirstFollow_1 (void)
{
  switch (CurToken) {
  case '(': case tok_identifier:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_2 (void)
{
  switch (CurToken) {
  case '+':
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_3 (void)
{
  switch (CurToken) {
  case ')': case ']': case expr_scan_EofToken:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_4 (void)
{
  switch (CurToken) {
  case '(': case tok_identifier:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_5 (void)
{
  switch (CurToken) {
  case '*':
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_6 (void)
{
  switch (CurToken) {
  case '+': case ')': case ']': case expr_scan_EofToken:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_7 (void)
{
  switch (CurToken) {
  case '(':
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_8 (void)
{
  switch (CurToken) {
  case tok_identifier:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_9 (void)
{
  switch (CurToken) {
  case tok_identifier:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_10 (void)
{
  switch (CurToken) {
  case '.':
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_11 (void)
{
  switch (CurToken) {
  case '[':
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_12 (void)
{
  switch (CurToken) {
  case tok_pd:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_13 (void)
{
  switch (CurToken) {
  case '*': case '+': case ')': case ']': case expr_scan_EofToken:
    return true;
  default:
    return false;
  }
}

  /* fill in the other FirstFollow-functions: FirstFollow_2() .. FirstFollow_8() */

/******************************************************************************
 * We use the following grammar for arithmetic expressions:
 * 1)  E  ::= T E1
 * 2)  E1 ::= + T E1       3)  E1 ::= epsilon
 * 4)  T  ::= F T1
 * 5)  T1 ::= * F T1       6)  T1 ::= epsilon
 * 7)  F  ::= ( E )        8)  F  ::= D
 * 9)  D  ::= id D1
 * 10) D1 ::= . id D1     11)  D1 ::= [ E ] D1
 * 12) D1 ::= -> id D1    13)  D1 ::= epsilon
 ******************************************************************************/

/* The function 'f_nt()' for the non-terminal 'nt' returns true, iff
 * 'CurToken' starts a sequence of input-tokens which may be generated by 'nt'.
 * 'CurToken' refers after that to the next token to be processed.
 * Note: eof = end-of-file  is a token too.
 */
bool f_E (void);
bool f_E1 (void);
bool f_T (void);
bool f_T1 (void);
bool f_F (void);
bool f_D (void);
bool f_D1 (void);


bool f_E (void)
{
  DEBUG_show("E");

  if (FirstFollow_1()) return f_T() && f_E1();
  Message ("Syntax Error in <E>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_E1 (void)
{
  DEBUG_show("E1");

  if (FirstFollow_2()) return match('+') && f_T() && f_T1();
  if (FirstFollow_3()) return true;
  Message ("Syntax Error in <E1>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_T (void)
{
  DEBUG_show("T");

  if (FirstFollow_4()) return f_F() && f_T1();
  Message ("Syntax Error in <T>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_T1 (void)
{
  DEBUG_show("T1");

  if (FirstFollow_5()) return match('*') && f_F() && f_T1();
  if (FirstFollow_6()) return true;
  
  Message ("Syntax Error in <T1>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_F (void)
{
  DEBUG_show("F");

  if (FirstFollow_7()) return match('(') && f_E() && match(')');
  if (FirstFollow_8()) return f_D();
  
  Message ("Syntax Error in <F>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_D (void)
{
  DEBUG_show("D");

  if (FirstFollow_9()) return match(tok_identifier) && f_D1();
  
  Message ("Syntax Error in <D>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_D1 (void)
{
  DEBUG_show("D1");

  if (FirstFollow_10()) return match('.') && match(tok_identifier) && f_D1();
  if (FirstFollow_11()) return match('[') && f_E() && match(']') && f_D1();
  if (FirstFollow_12()) return match(tok_pd) && match(tok_identifier) && f_D1();
  if (FirstFollow_13()) return true;
  
  Message ("Syntax Error in <D1>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

/* fill in the functions for the other non-terminals */

/***********************  E  N  D  ***********************************************/
