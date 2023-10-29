#ifndef _INCLUDE_SIGPROG_H
#define _INCLUDE_SIGPROG_H

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "../include/customtypes.h"

double complex* Sigproc_DFT(double complex** samples, u16 sampleCount);

#endif