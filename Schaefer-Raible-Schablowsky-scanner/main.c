#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Position.h"
#include "l_scan.h"

int main (int argc, char *argv[]) {
	int Token, Count = 0;
	if (argc == 2) {
		if (strcmp (argv[1], "-h") == 0) {
			fprintf (stderr,
				"usage: scan [-h] [file]\n"
				"  simple scanner, reads `file' or stdin\n"
				"  -h: Help\n");
			exit (0);
		}
		
		l_scan_Attribute.Position.FileName = MakeIdent1 (argv[1]);
		l_scan_BeginFile (argv[1]);
		/* Read from file argv[1].
		 * If this routine is not called, stdin is read.
		 */
	}
	
	for (Token = l_scan_GetToken(); Token != l_scan_EofToken; Token = l_scan_GetToken()) {
		Count++;
		WritePosition(stdout, l_scan_Attribute.Position); printf (" ");
		switch (Token) {
			case tok_int_const:
				printf("int_const     : %ld\n", l_scan_Attribute.int_const.Value);
				break;
			case tok_float_const:
				printf("float_const   : %f\n", l_scan_Attribute.float_const.Value);
				break;
			case tok_string_const:
				printf("string_const  : %s\n", StGetCStr(l_scan_Attribute.string_const.Value));
				break;
			case tok_prog:
				printf("prog token\n");
				break;
			case tok_var:
				printf("var token\n");
				break;
			case tok_end_var:
				printf("end_var token\n");
				break;
			case tok_exec:
				printf("exec token\n");
				break;
			case tok_end_exec:
				printf("end_exec token\n");
				break;
			case tok_dot:
				printf("dot token\n");
				break;
			case tok_var_input:
				printf("variable input token\n");
				break;
			case tok_var_output:
				printf("variable output token\n");
				break;
			case tok_bracket_open:
				printf("bracket open ( token\n");
				break;
			case tok_bracket_close:
				printf("bracket close ) token\n");
				break;
			case tok_var_type:
				printf("variable type : ");
				switch(l_scan_Attribute.var_type.Type) {
					case VT_INT:
						printf("int\n");
						break;
					case VT_FLOAT:
						printf("float\n");
						break;
					case VT_STRING:
						printf("string\n");
						break;
				}
				break;
			case tok_begin:
				printf ("begin token\n");
				break;
			case tok_end:
				printf ("end token\n");
				break;
			case tok_if:
				printf("if token\n");
				break;
			case tok_then:
				printf("then token\n");
				break;
			case tok_else:
				printf ("else token\n");
				break;
			case tok_endif:
				printf ("endif token\n");
				break;
			case tok_for:
				printf("for token\n");
				break;
			case tok_do:
				printf ("do token\n");
				break;
			case tok_endfor:
				printf ("endfor token\n");
				break;
			case tok_while:
				printf ("while token\n");
				break;
			case tok_endwhile:
				printf ("endwhile token\n");
				break;
			case tok_assign_op:
				printf("assign oper   : ");
				switch(l_scan_Attribute.assign_op.Type) {
					case AO_EQUALS:
						printf("=\n");
						break;
					case AO_PLUSEQ:
						printf("+=\n");
						break;
					case AO_MINUSEQ:
						printf("-=\n");
						break;
					case AO_MULEQ:
						printf("*=\n");
						break;
					case AO_DIVEQ:
						printf("/=\n");
						break;
				}
				break;
			case tok_relational_op:
				printf("relation oper : ");
				switch(l_scan_Attribute.relational_op.Type) {
					case RO_EQUALS:
						printf("==\n");
						break;
					case RO_NOTEQUAL:
						printf("~=\n");
						break;
					case RO_LESS:
						printf("<\n");
						break;
					case RO_GREATER:
						printf(">\n");
						break;
					case RO_LESSEQ:
						printf("<=\n");
						break;
					case RO_GREATEREQ:
						printf(">=\n");
						break;
				}
				break;
			case tok_condition_op:
				printf("condition op  : ");
				switch(l_scan_Attribute.condition_op.Type) {
					case CO_AND:
						printf("&&\n");
						break;
					case CO_OR:
						printf("||\n");
						break;
				}
				break;
			case tok_plus:
				printf("plus + token\n");
				break;
			case tok_minus:
				printf("minus - token\n");
				break;
			case tok_mul:
				printf("mul * token\n");
				break;
			case tok_div:
				printf("div / token\n");
				break;
			case tok_not:
				printf("not ~ token\n");
				break;
			case tok_identifier:
				printf("identifier    : %s\n", GetCStr(l_scan_Attribute.identifier.Ident));
				break;
			default: fprintf(stderr, "FATAL ERROR, unknown token\n");
		}
	}
	
	printf ("Token count: %d\n", Count);
	return 0;
}
