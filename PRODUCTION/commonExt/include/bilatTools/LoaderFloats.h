#ifndef LOADERFLOATS_H
#define LOADERFLOATS_H

#include "envTools.h"

#include <iostream>
#include <string.h>
using std::string;


/**
 * Return NULL if it's not a valid fileName !
 */
CBI_TOOLS float* loadFloat(string fileName,unsigned int nbElements);


#endif
