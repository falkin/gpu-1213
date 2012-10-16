#ifndef LOADERUCHARS_H
#define LOADERUCHARS_H

#include "envTools.h"

#include <string.h>
using std::string;

/**
 * Return NULL if it's not a valid fileName !
 */
CBI_TOOLS unsigned char* loadUnsignedChars(string fileName, int nbElements);

#endif /* LOADERUCHARS_H*/
