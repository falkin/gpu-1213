# Version 	: 0.0.1
# Date		: 26.01.2012
# Author 	: Cedric.Bilat@he-arc.ch
#
# Contrainte
#
#	Dans les definitions de variables ci-dessous, ne laisser jamais d'espace a la fin!!!
#

##############
#   public   #
##############

SRC_AUX+=../PRODUCTION/commonExt/include
SRC_AUX+=../PRODUCTION/commonExt/windows

#########
# Visual #
#########

#separateur est espace,sans extension .a, sans prefixe lib
EXCLUDE_LIBRARY_FILES:=
ADD_LIBRARY_FILES:=

#Compilation: (minimal conseillé : /MD)
CXXFLAGS:= /MD#pour linker lib
CXXFLAGS+= /Ox 
CXXFLAGS+= /openmp

# OMP
# 	Visual 2008 cuda 4.1
# 		bug : /openmp ne peut pas etre use with cu files
# 		Solution : 	compile cu files without /openmp 
# 					compile .ccp file with /openmp
# 		Tip:		compile all file without /openmp
#					modify file usinf omp
#					compile with flag /openmp
# 		Conclusion : with this technique omp ok !
#	Visual 2010 cuda 4.1
# 		bug : fix
#		Conclusion : On peut compiler/linker avec /openmp
#	Linux : ok
#

#Linkage: (minimal vide)
CXXLDFLAGS :=

#" " pas necessaire pour CXXLDFLAGS et CXXFLAGS, post-added!
#flag seront surcharger par la suite

##############
#   pivate   #
##############

COMPILATEUR:=nvidia
OS:=Win
USER=${USERNAME}

#chargement de la makeFile principale
-include dataProject.mk
-include ../PRODUCTION/MANAGER/makefile/private/makeFileCudaWin.mk
 
##############
#   END      #
##############
