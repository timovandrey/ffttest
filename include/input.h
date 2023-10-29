#include "types.h"
#include "complex.h"

typedef enum input_status_s
{
    INPUT_ERROR = -1,
    INPUT_SUCCESS,
    INPUT_STATUS_COUNT,
    INPUT_UNDEFINED = 0xff
} input_status;

input_status Input_readFile(char* fileNameAndPath, u16* sampleCount, double complex* samples);
input_status Input_writeFile(char* fileNameAndPath, u16* sampleCount, double complex* frequencyBins);

