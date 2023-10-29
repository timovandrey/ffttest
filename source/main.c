#include "../include/main.h"
#include <stdlib.h> 

int main(int argc, char** argv)
{
    printf("Started program ...\n");  

    input_status readState = INPUT_UNDEFINED, writeState = INPUT_UNDEFINED;
    u16 N = 0;
    double complex *samples, *bins;

    readState = Input_readFile(SAMPLE_FILE, &N, &samples);
    if(N == 0 || samples == NULL || readState == INPUT_ERROR || readState == INPUT_UNDEFINED)
    {
        printf("Error while reading the file. Exiting ...");
        return 1;
    }

    /* Print samples */
    // for(int i = 0; i < N; i++)
    // {
    //     printf("Sample[%04d] = %02.2f + j%02.2f\n", i, creal(samples[i]), cimag(samples[i]));
    // }

    bins = Sigproc_DFT(&samples, N);

    /* Writing the calculated frequencies */
    writeState = Input_writeFile(SPECTRUM_FILE, N, samples);
    if(writeState == INPUT_ERROR || writeState == INPUT_UNDEFINED)
    {
        printf("Error while writing the file. Exiting ...");
        return 1;
    }

    /* Free all dynamically allocated memory */
    free(samples);
    free(bins);

    printf("... done.\n");  
    return 0;
}