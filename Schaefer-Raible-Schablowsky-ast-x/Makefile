###############################################################################
# Project:  COCKTAIL training
# Descr:    A simple pocket computer (scanner, parser, evaluator)
# Kind:     Makefile
# Author:   Prof. Dr. Juergen Vollmer <vollmer@dwbw-karlsruhe.de>
# $Id: Makefile,v 1.9 2018/12/07 10:44:52 vollmer Exp $
###############################################################################

# The executable to produce:
MAIN		= x-ast

# Source files
SRC_C		= main.c
SRC		= x.scan 	        \
		  x.pars	\
		  x.ast 	\

# Generated files
GEN_C		= x_scan.c x_scanSource.c x_pars.c Tree.c
GEN_H		= x_scan.h x_scanSource.h x_pars.h Tree.h yyTree.h
GEN		= x.rex x_scan.rpp x_pars.lrk      Tree.TS

###############################################################################

include ../config.mk

###############################################################################

# Create your parser
all: $(MAIN)

# Run the test suite
test:
	./$(MAIN) ggt.x; echo
	./$(MAIN) faculty.x; echo
	./$(MAIN) calc_n.x; echo
	./$(MAIN) test1.x; echo
	./$(MAIN) test2.x; echo
	./$(MAIN) test3.x; echo
	./$(MAIN) test4.x; echo
	./$(MAIN) test5.x; echo
	./$(MAIN) test6.x; echo

###############################################################################

# Create the Parser
x_pars.lrk x_scan.rpp: x.pars
	lpp -cxzj  x.pars

LARK_OPTS = -cdi -Dw -5  # -5 ==> create the graphic LR-browser
LARK_OPTS = -cdi -Dw     #    ==> see ../config.mk
x_pars.c x_pars.h: x_pars.lrk
	lark $(LARK_OPTS) x_pars.lrk

# Create the Scanner
x.rex: x.scan x_scan.rpp
	rpp < x.scan x_scan.rpp > x.rex

x_scan.c x_scan.h x_scanSource.c x_scanSource.h: x.rex
	rex -cdis -y x.rex
	rm -f x_scanDrv.c

# Create the Abstract Syntax Tree module
# AST options
# -a generate all except -ceh (default)
# -4 generate tree/graph description in file TREE.TS
# -c generate C    source code
# -d generate header file or definition module
# -i generate implementation part or module
# -w generate text graph writer    WriteTREE
# -R generate list reverser        ReverseTREE, ForallTREE
# -t generate top down  traversal  TraverseTREETD
# -b generate bottom up traversal  TraverseTREEBU
# -k generate graph type checker   CheckTREE
# -q generate text  graph browser  QueryTREE
# -e generate graphic browser      procedure DrawTREE
Tree.TS Tree.c Tree.h yyTree.h: x.ast
	ast -cdi -4wemRk x.ast

###############################################################################

include ../common.mk

###############################################################################
