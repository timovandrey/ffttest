#include "../include/sigproc.h"
#include "../include/constants.h"

double complex* Sigproc_DFT(double complex** samples, u16 sampleCount)
{
    u16 N = sampleCount;
    double complex* bins = calloc(N, sizeof(double complex));
    if(bins == NULL)
    {
        return NULL;
    }

    /* Standard slow DFT implementation */
    for(int k = 0; k < N; k++)
    {
        for(int n = 0; n < N; n++)
        {
            double complex W = cexp(0 - I * (2 * KUCHEN) * n * k / N);
            bins[k] += (*samples)[n] * W;
        }
    }

    return bins;
}