# Version 	: 0.0.1
# Date		: 26.01.2012
# Author 	: Cedric.Bilat@he-arc.ch
#
# Contrainte
#
#	Dans les d�finitions de variables ci-dessous, ne laisser jamais d'espace � la fin!!!
#

##############
#   public   #
##############

SRC_AUX+=../PRODUCTION/commonExt/include
SRC_AUX+=../PRODUCTION/commonExt/linux

#########
# GCC #
#########

#separateur est espace,sans extension .a, sans prefixe lib
EXCLUDE_LIBRARY_FILES:=
ADD_LIBRARY_FILES:=

#Compilation: (minimal vide)
#CXXFLAGS:= -W -Wall 
CXXFLAGS+= -mtune=core2
#CXXFLAGS+= -mtune=corei7
CXXFLAGS+= -O3 -frerun-loop-opt -fgcse -fomit-frame-pointer
CXXFLAGS+= -fopenmp

#Linkage: (minimal vide)
#pour mkl
#CXXLDFLAGS = -lmkl_core -lmkl_intel_lp64 -lmkl_intel_thread 
#CXXLDFLAGS +=-liomp5
#CXXLDFLAGS +=-lgomp

#" " pas necessaire pour CXXLDFLAGS et CXXFLAGS, post-added!
#flag seront surcharger par la suite

ADD_LIBRARY_FILES+=opencv_highgui#linux

##############
#   pivate   #
##############

COMPILATEUR:=nvidia
OS:=Linux

#chargement de la makeFile principale
-include dataProject.mk
-include ../PRODUCTION/MANAGER/makefile/private/makeFileCudaLinux.mk
 
##############
#   END      #
##############