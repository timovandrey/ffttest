#include "input.h"
#include "stdlib.h"
#include "stdio.h"

input_status Input_readFile(char* fileNameAndPath, u16* sampleCount, double complex* samples)
{
    /* Open file and check for errors*/
    FILE* file = fopen(fileNameAndPath, "rb");
    if(file == NULL)
    {
        return INPUT_ERROR;
    }

    /* Read first data bit in file and allocate memory for sample data */
    int cnt = fread(sampleCount, sizeof(u16), 1, file);
    if(*sampleCount == NULL || cnt != 1)
    {
        return INPUT_ERROR;
    }

    /* Allocate memory for samples */
    samples = calloc(*sampleCount, sizeof(double complex));
    if(samples == NULL)
    {
        return INPUT_ERROR;
    }

    /* Read all samples */
    for(u64 idx = 0; ((idx < *sampleCount) || (file == EOF)); idx++)
    {
        double real, imaginary;
        int cnt = -1;
        cnt = fread(&real, sizeof(double), 1, file);
        if(cnt != 1)
        {
            return INPUT_ERROR;
        }
        cnt = fread(&imaginary, sizeof(double), 1, file);
        if(cnt != 1)
        {
            return INPUT_ERROR;
        }
        samples[idx] = real + imaginary * I;
    }

    fclose(file);
}

input_status INPUT_writeFile(char* fileNameAndPath, u16* sampleCount, double complex* frequencyBins)
{

}