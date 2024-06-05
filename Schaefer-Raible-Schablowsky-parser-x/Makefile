###############################################################################
# Project:  COCKTAIL training
# Descr:    LR parser for an xession language
# Kind:     Makefile
# Author:   Dr. Juergen Vollmer <Juergen.Vollmer@informatik-vollmer.de>
# $Id: Makefile,v 1.5 2007/06/03 16:52:25 vollmer Exp $
###############################################################################

# The executable to produce:
MAIN		= lr-parser

# Source files
SRC_C		= main.c
SRC_H		=
SRC		= x.scan x.pars

# Generated files
GEN_C		= x_scan.c x_scanSource.c x_pars.c
GEN_H		= x_scan.h x_scanSource.h x_pars.h
GEN		= x.rex x_scan.rpp x_pars.lrk

###############################################################################

include ../config.mk

###############################################################################

# Create your parser
all: $(MAIN)

# Run the test suite
test:
	./$(MAIN) ggt.x; echo
	./$(MAIN) faculty.x; echo
	./$(MAIN) test1.x; echo
	./$(MAIN) test2.x; echo
	./$(MAIN) test3.x; echo
	./$(MAIN) test4.x; echo
	./$(MAIN) test5.x; echo
	./$(MAIN) test6.x; echo


tar: clean
	cd .. && tar -czvf Schaefer-Raible-Schablowsky.tar.gz Schaefer-Raible-Schablowsky

###############################################################################

# Create the Parser
x_pars.lrk x_scan.rpp: x$(SOLUTION).pars
	lpp -cxzj x$(SOLUTION).pars

LARK_OPTS = -cdi -Dw -5  # -5 ==> create the graphic LR-browser
LARK_OPTS = -cdi -Dw     #    ==> see ../config.mk
x_pars.c x_pars.h: x_pars.lrk
	lark $(LARK_OPTS) x_pars.lrk

# Create the Scanner
x.rex:	x.scan x_scan.rpp
	rpp < x.scan x_scan.rpp > x.rex

x_scan.c x_scan.h x_scanSource.c x_scanSource.h: x.rex
	rex -cdis -y x.rex
	rm -f x_scanDrv.c

###############################################################################

include ../common.mk

###############################################################################
