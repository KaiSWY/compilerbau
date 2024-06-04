###############################################################################
# Project:  COCKTAIL training
# Descr:    Directory with all programming excercies
# Kind:     Makefile
# Author:   Prof. Dr. Juergen Vollmer <vollmer@dhbw-karlsruhe.de>
# $Id: Makefile,v 1.39 2020/10/03 15:49:27 vollmer Exp $
###############################################################################

NEXT_DIR  = $(HOME)/Nextcloud/DHBW/vorlesungen/übersetzerbau
# NEXT_DIR  = $(HOME)/bwsync/DHBW/vorlesungen/übersetzerbau

dirs	=  rPrepro				        \
	   hello dea scanner recursive-decent lr-parser \
	   recursive-decent-2				\
	   ast-c ast-java				\
	   expr expr-calc expr-ast expr-eval expr-trip	\
	   expr-stmt expr-ag 				\
	   code-stack				        \
	   expr-stmt-testat				\
	   minilax					\
	   oberon-loesung

ALL:
	@echo "Makefile für die Beispielprogramme"
	@echo "bitte ein Ziel angeben:"
	@echo "  all"
	@echo "  clean"
	@echo "  tar"
	@echo "  tar-solutions"

all depend test solution:
	@for d in $(dirs); 				\
	 do 						\
	   echo;echo "***** visiting $$d"; echo;	\
	   $(MAKE) -C $$d $@;				\
	 done || true

mk-sources::
	$(MAKE) -C rPrepro


clean real-clean delete-sources mk-sources::
	@for d in $(dirs); 				\
	 do 						\
	   echo "***** visit $$d and make $@";		\
	   $(MAKE) -s -C $$d $@;			\
	 done || true
	@find . -name "*~" -o -name "core*" -o -name "#*" | xargs rm -f

###############################################################################

TAR_FILE = programme-`date "+%Y-%m-%d"`.tgz
TAR_EX   = --exclude "RCS" --exclude src --exclude "*.tgz" \
	   --exclude "minilax"        				\
	   --exclude "oberon-loesung" 				\
	   --exclude "*-testat"	      				\
	   --exclude "scanner-joern"  				\
	   --exclude "recursive-decent-2/parser-solution.c" 	\
	   --exclude "lang-x"                                   \
	   --exclude "recursive-decent-full"			\
	   --exclude "studis"                                   \
	   --exclude "recursive-decent-2/test.*.0[345]"

tar: mk-sources real-clean
	@rm -f $(TAR_FILE);		       				\
	 chmod u+w */* ;                                                \
	 cd ..; 						       	\
	 echo "***** tar sources";					\
	 tar $(TAR_EX) -czvf $(TAR_FILE) programme;			\
	 rm -f $(NEXT_DIR)/programme-*.tgz;				\
	 cp -ap $(TAR_FILE) $(NEXT_DIR)

###############################################################################

diff:
	@ echo "check for diff's to RCS";			\
	for d in `find . -type d -not -wholename "*RCS"`;	\
	do							\
         (							\
	   if [ -d $$d ] && [ -d $$d/RCS ]; 			\
	   then							\
	    echo "  check directory $$d";			\
	    cd $$d;						\
	    if [ -d RCS ];					\
	    then 						\
	     if [ `rlog  -L  -R  RCS/* | wc -l` -ne 0 ] ;	\
	     then 						\
	        echo "       - files which have locks set: "; 	\
	        for f in `rlog  -L  -R  RCS/*`;			\
	        do						\
		   echo "        " `basename $$f ,v`;		\
		done;						\
	     fi;						\
	     for f in RCS/* ; 					\
	     do							\
	        if [ -f `basename $$f ,v` ] ;			\
		then						\
		   x=`rcsdiff -q $$f | 			        \
		      sed -e'/Id: [^,]*,v/d' 			\
		          -e'/Date: .*\/.*\/.* .*:.*:.* \\$$/d'	\
		          -e'/Revision: [0-9\.]* \\$$/d'	\
		          -e'/Log: [^,]*,v/d'			\
			  -e'/^---$$/d'      			\
			  -e'/^[0-9,]*c[0-9,]*/d' | 		\
		      wc -l`;					\
		   if [ $$x -ne 0 ];				\
		   then 					\
		     ff="$$d/"`basename $$f ,v`;		\
		     echo "  ** $$ff has diffs to RCS";		\
		   fi;						\
	        fi;						\
	     done;						\
	    fi;							\
	   fi;							\
	  );							\
	done
##############################################################################
