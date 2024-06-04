/* Project:  COCKTAIL training
 * Descr:    A simple pocket computer (scanner, parser, evaluator)
 * Kind:     Some commonly used typedef's and functions
 * Author:   Prof. Dr. Juergen Vollmer <vollmer@dhbw-karlsruhe.de>
 * $Id: util.h,v 1.8 2022/04/29 13:24:40 vollmer Exp $
 */

# ifndef UTIL_H
# define UTIL_H

# include <stdio.h>
# include <stdlib.h>
# include "Position.h"

typedef FILE *tFILE;

/*****************************************************************************
 * Enumerate all unary, binary operators, and names of function
 ****************************************************************************/
typedef enum  {
   op_none      /* "undefinied" value */
  ,op_plus      /*  +  */
  ,op_minus     /*  -  */
  ,op_mult      /*  *  */
  ,op_div       /*  /  */
  ,op_mod       /*  %  modulo        */
  ,op_pow       /*  ** power         */
  ,op_lt        /*  <  less then     */
  ,op_le        /*  <= less equal    */
  ,op_gt        /*  >  greater then  */
  ,op_ge        /*  >= greater equal */
  ,op_eq        /*  == equal         */
  ,op_ne        /*  != not equal     */
  ,op_not       /*  !  boolean not   */
  ,op_and       /*  &  boolean and   */
  ,op_or        /*  |  boolean or    */
  ,op_in
  ,op_div2
  ,op_is
} tOperator;

extern const char *operator2string (tOperator op);
/* mapping from a tOperator value to a string */

/* The following is used by files generated by the AST tool as part of the generated
 * interface
 */
 /* output of an operator `op' to `file' */
 # define fprintf_tOperator(file, op)  fprintf (file, "%s", operator2string(op));

 /* `writeTYPE(val)' is used by the generated AST routines to print a textual
  * representation of a value of the user defined type TYPE.
  * The output is written to file `yyf' (a global FILE* variable set somewhere)
  */
 # define writetOperator(val) fprintf_tOperator (yyf, val);

 /* `beginTYPE' is used by the generated AST routines to initailize a
  * value of the user defined type TYPE, if no explicit value is given
  * when constructing a node having a field of this type.
  * (e.g. the attribute `ReqRegs' below).
  */
 # define begintOperator(val)  val = op_none;

 /* `equalTYPE' is used by the generated AST routines to compare two values
  * for equality
  */
 # define equaltOperator(a,b)  ((a) == (b))

 /* For the usual C-types (int, char, * etc.) the file `yyTREE.h' contains
  * some default definitions, for `writeTYPE', `beginTYPE' and
  * other routines (see the manuals).
  * By simply defining e.g. `writeint' here, the default is not used.
  */

/*****************************************************************************
 * computing floting point values from  floating point values
 ****************************************************************************/
extern double evalUnary (tOperator op, double argument, tPosition pos);
/* compute "op argument" */

extern double evalBinary (tOperator op, double left, double right, tPosition pos);
/* compute "left op right" */

/*****************************************************************************
 * Enumerate all data types used by our simple languages
 ****************************************************************************/
typedef enum  {
   type_error  /* undefined, error type */
  ,type_none
  ,type_void
  ,type_bool
  ,type_int
  ,type_float
  ,type_func
  ,type_array
} tType;

  extern const char *type2string (tType type);
 # define fprintf_tType(file, type)  fprintf (file, "%s", type2string(type));
 # define writetType(val) fprintf_tType (yyf, val);
 # define begintType(val) val = type_none;
 # define equaltType(a,b) ((a) == (b))

/*****************************************************************************
 * Enumerate all kinds of coercions
 ****************************************************************************/

typedef enum {
   coerce_none
  ,coerce2bool
  ,coerce2int
  ,coerce2float
} tCoercion;

  extern const char *coercion2string (tCoercion co);
 # define fprintf_tCoercion(file, type)  fprintf (file, "%s", coercion2string(type));
 # define writetCoercion(val) fprintf_tCoercion (yyf, val);
 # define begintCoercion(val) val = coerce_none;
 # define equaltCoercion(a,b) ((a) == (b))

# define is_numeric_type(t) ((t) == type_int  || (t) == type_float)

extern tType result_type   (tOperator op, tType left, tType right, tPosition pos);
/* Returns the result type of an operator depending on the argument types.
 * For unary operators, pass "right = type_none"
 * An error message is emitted, if the types are not corecible.
 */

extern tType argument_type (tOperator op, tType left, tType right, tPosition pos);
/* Returns the destination type the arguments must have for the given operator.
 * Both operands of a binary operator must have the same destination type.
 * For unary operators, pass "right = type_none"
 * An error message is emitted, if the types are not corecible.
 */

/*****************************************************************************
 * Support programming error handling
 ****************************************************************************/

# define FATAL_ERROR() 								      \
  {fprintf (stderr, "fatal error: file %s, line %d\n", __FILE__ , __LINE__); abort(); }
/* Indicate a programming error
 * __FILE__  the filename of the source file "calling" the macro
 * __LINE__  the line "calling" this macro
 */

# endif
