#ifndef LOADERINTEGERS_H
#define LOADERINTEGERS_H

#include "envTools.h"

#include <string.h>
using std::string;

CBI_TOOLS int* loadInteger(string fileName, int nbElements);

CBI_TOOLS unsigned int* loadUnsignedInteger(string fileName, int nbElements);


#endif /* LOADERINTEGERS_H */
