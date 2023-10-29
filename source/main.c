#include "../include/main.h"
#include "../include/input.h"
#include "../include/constants.h"

int main(int argc, char** argv)
{
    printf("Started program ...\n");  

    input_status readState = INPUT_UNDEFINED;

    u16 N = 0;
    double complex *samples = NULL;
    readState = Input_readFile(SAMPLE_FILE, &N, samples);
    if(N == 0 || samples == NULL || readState == INPUT_ERROR || readState == INPUT_UNDEFINED)
    {
        printf("Error while reading the file. Exiting ...");
        return 1;
    }




    printf("... done.\n");  
    return 0;
}