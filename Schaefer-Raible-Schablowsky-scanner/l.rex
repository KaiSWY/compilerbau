SCANNER l_scan

EXPORT {
#include "Position.h"

typedef enum { VT_INT, VT_FLOAT, VT_STRING } vVarType;

typedef enum { AO_EQUALS, AO_PLUSEQ, AO_MINUSEQ, AO_MULEQ, AO_DIVEQ } vAssignOp;
typedef enum { RO_EQUALS, RO_NOTEQUAL, RO_LESS, RO_GREATER, RO_LESSEQ, RO_GREATEREQ } vRelationalOp;
typedef enum { CO_AND, CO_OR } vConditionOp;

/* Token Attributes */
typedef struct {tPosition Pos; long Value;} tint_const;
typedef struct {tPosition Pos; double Value;} tfloat_const;
typedef struct {tPosition Pos; tStringRef Value;} tstring_const;

typedef struct {tPosition Pos; vVarType Type;} tvar_type;

typedef struct {tPosition Pos; vAssignOp Type;} tassign_op;
typedef struct {tPosition Pos; vRelationalOp Type;} trelational_op;
typedef struct {tPosition Pos; vConditionOp Type;} tcondition_op;

typedef struct {tPosition Pos; tIdent Ident;} tidentifier;

/* Token Attribute Union */
typedef union {
  tPosition       Position;
  tint_const      int_const;
  tfloat_const    float_const;
  tstring_const   string_const;
  
  tvar_type       var_type;
  
  tassign_op      assign_op;
  trelational_op  relational_op;
  tcondition_op   condition_op;
  
  tidentifier   identifier;
} l_scan_tScanAttribute;

/* Token Codes */
#define tok_int_const     1
#define tok_float_const   2
#define tok_string_const  3

#define tok_prog          4
#define tok_var           5
#define tok_end_var       6
#define tok_exec          7
#define tok_end_exec      8

#define tok_dot           9
#define tok_var_input     10
#define tok_var_output    11
#define tok_bracket_open  12
#define tok_bracket_close 13

#define tok_var_type      15

#define tok_begin         16
#define tok_end           17

#define tok_if            18
#define tok_then          19
#define tok_else          20
#define tok_endif         21

#define tok_for           22
#define tok_do            23
#define tok_endfor        24

#define tok_while         25
#define tok_endwhile      26

#define tok_assign_op     27
#define tok_relational_op 28
#define tok_condition_op  29

#define tok_plus          30
#define tok_minus         31
#define tok_mul           32
#define tok_div           33
#define tok_not           34

#define tok_identifier    35
} // EXPORT

GLOBAL {
#include <stdlib.h>
#include "rString.h"
} // GLOBAL

LOCAL {
  /* variables for string scanning */
  char stringBuffer[1024];
  int stringLen = 0;
  tPosition stringPos;
}  // LOCAL

DEFAULT {
  /* What happens if no scanner rule matches the input */
  MessageI ("Illegal character", xxError, l_scan_Attribute.Position, xxCharacter, l_scan_TokenPtr);
} // DEFAULT

EOF {
  /* What should be done if the end-of-input-file has been reached? */

  /* E.g.: check that strings and comments are closed. */
  switch (yyStartState) {
    case STD:
      /* ok */
      break;
    case STRING:
      Message ("string literal not closed", xxError, stringPos);
      break;
    case CMT:
      Message ("c comment not closed", xxFatal, l_scan_Attribute.Position);
      break;
    default:
      Message ("OOPS: that should not happen!!", xxFatal, l_scan_Attribute.Position);
      break;
  }

  /* implicit: return the EofToken */
} // EOF

DEFINE  /* some abbreviations */
  digit = {0-9}        .
  letter = {a-zA-Z}    .
  A  = {Aa}            .
  B  = {Bb}            .
  C  = {Cc}            .
  D  = {Dd}            .
  E  = {Ee}            .
  F  = {Ff}            .
  G  = {Gg}            .
  H  = {Hh}            .
  I  = {Ii}            .
  J  = {Jj}            .
  K  = {Kk}            .
  L  = {Ll}            .
  M  = {Mm}            .
  N  = {Nn}            .
  O  = {Oo}            .
  P  = {Pp}            .
  Q  = {Qq}            .
  R  = {Rr}            .
  S  = {Ss}            .
  T  = {Tt}            .
  U  = {Uu}            .
  V  = {Vv}            .
  W  = {Ww}            .
  X  = {Xx}            .
  Y  = {Yy}            .
  Z  = {Zz}            .
/* define start states, note STD is defined by default, separate several states by a comma */
/* START STRING */

START STRING, CMT

RULE

/* Integers */
#STD# digit+ : {
  l_scan_Attribute.int_const.Value = atol(l_scan_TokenPtr);
  return tok_int_const;
}

/* Float numbers */
#STD# digit+ "." digit+ : {
  l_scan_Attribute.float_const.Value = atof(l_scan_TokenPtr);
  return tok_float_const;
}

/* double quote delimited strings */
#STD# \" : {
  yyStart(STRING);
  stringLen = 0;
  stringPos = l_scan_Attribute.Position;
}

#STRING# \" : {
  yyStart(STD);
  l_scan_Attribute.string_const.Value = PutString(stringBuffer, stringLen);
  return tok_string_const;
}

#STRING# \\ \n : {
  stringBuffer[stringLen] = '\n';
  stringLen++;
}

#STRING# \\ \" : {
  stringBuffer[stringLen] = '"';
  stringLen++;
}

/* TODO: Add all escaped string chars */

#STRING# \n : {
  Message("line break in string", xxError, l_scan_Attribute.Position);
}

#STRING# ANY : {
  stringBuffer[stringLen] = *l_scan_TokenPtr;
  stringLen++;
}

/* PROG */
#STD# "PROG" : {
  return tok_prog;
}

/* VAR */
#STD# "VAR" : {
  return tok_var;
}

/* END_VAR */
#STD# "END_VAR" : {
  return tok_end_var;
}

/* EXEC */
#STD# "EXEC" : {
  return tok_exec;
}

/* END_EXEC */
#STD# "END_EXEC" : {
  return tok_end_exec;
}

/* . */
#STD# "." : {
  return tok_dot;
}

/* ? */
#STD# "?" : {
  return tok_var_input;
}

/* ! */
#STD# "!" : {
  return tok_var_output;
}

/* ( */
#STD# "(" : {
  return tok_bracket_open;
}

/* ) */
#STD# ")" : {
  return tok_bracket_close;
}

/* variable types */
#STD# "int" : {
  l_scan_Attribute.var_type.Type = VT_INT;
  return tok_var_type;
}

#STD# "float" : {
  l_scan_Attribute.var_type.Type = VT_FLOAT;
  return tok_var_type;
}

#STD# "string" : {
  l_scan_Attribute.var_type.Type = VT_STRING;
  return tok_var_type;
}


/* begin */
#STD# begin : {
  return tok_begin;
}

/* end */
#STD# end : {
  return tok_end;
}

/* if */
#STD# if : {
  return tok_if;
}

/* then */
#STD# then : {
  return tok_then;
}

/* else */
#STD# else : {
  return tok_else;
}

/* endif */
#STD# endif : {
  return tok_endif;
}

/* for */
#STD# for : {
  return tok_for;
}

/* do */
#STD# do : {
  return tok_do;
}

/* endfor */
#STD# endfor : {
  return tok_endfor;
}

/* while */
#STD# while : {
  return tok_while;
}

/* endwhile */
#STD# endwhile : {
  return tok_endwhile;
}

/* assign operators */
#STD# "=" : {
  l_scan_Attribute.assign_op.Type = AO_EQUALS;
  return tok_assign_op;
}

#STD# "+=" : {
  l_scan_Attribute.assign_op.Type = AO_PLUSEQ;
  return tok_assign_op;
}

#STD# "-=" : {
  l_scan_Attribute.assign_op.Type = AO_MINUSEQ;
  return tok_assign_op;
}

#STD# "*=" : {
  l_scan_Attribute.assign_op.Type = AO_MULEQ;
  return tok_assign_op;
}

#STD# "/=" : {
  l_scan_Attribute.assign_op.Type = AO_DIVEQ;
  return tok_assign_op;
}

/* relational operators */
#STD# "==" : {
  l_scan_Attribute.relational_op.Type = RO_EQUALS;
  return tok_relational_op;
}

#STD# "~=" : {
  l_scan_Attribute.relational_op.Type = RO_NOTEQUAL;
  return tok_relational_op;
}

#STD# "<" : {
  l_scan_Attribute.relational_op.Type = RO_LESS;
  return tok_relational_op;
}

#STD# ">" : {
  l_scan_Attribute.relational_op.Type = RO_GREATER;
  return tok_relational_op;
}

#STD# "<=" : {
  l_scan_Attribute.relational_op.Type = RO_LESSEQ;
  return tok_relational_op;
}

#STD# ">=" : {
  l_scan_Attribute.relational_op.Type = RO_GREATEREQ;
  return tok_relational_op;
}

/* condition operators */
#STD# "&&" : {
  l_scan_Attribute.condition_op.Type = CO_AND;
  return tok_condition_op;
}

#STD# "||" : {
  l_scan_Attribute.condition_op.Type = CO_OR;
  return tok_condition_op;
}

/* + */
#STD# "+" : {
  return tok_plus;
}

/* - */
#STD# "-" : {
  return tok_minus;
}

/* * */
#STD# "*" : {
  return tok_mul;
}

/* / */
#STD# "/" : {
  return tok_div;
}

/* ~ */
#STD# "~" : {
  return tok_not;
}

/* identifiers */
#STD# letter (letter | digit)* : {
  l_scan_Attribute.identifier.Ident = MakeIdent(l_scan_TokenPtr, l_scan_TokenLength);
  return tok_identifier;
}

/* comments */
#STD# "/*" : {
  yyStart(CMT);
}

#CMT# "*/" : {
  yyStart(STD);
}

#CMT# ANY : {}
