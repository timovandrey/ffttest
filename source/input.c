#include "../include/input.h"
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

input_status Input_readFile(char* fileNameAndPath, u16* sampleCount, double complex** samples)
{
    /* Open file and check for errors*/
    input_status status = INPUT_UNDEFINED;
    FILE* file = fopen(fileNameAndPath, "rb");
    if(file == NULL)
    {
        status = INPUT_ERROR;
        goto GT_CLOSE_FILE;
    }

    /* Read first data bit in file and allocate memory for sample data */
    int cnt = fread(sampleCount, sizeof(u16), 1, file);
    if(sampleCount == NULL || cnt != 1)
    {
        status = INPUT_ERROR;
        goto GT_CLOSE_FILE;
    }

    /* Allocate memory for samples */
    *samples = calloc(*sampleCount, sizeof(double complex));
    if(*samples == NULL)
    {
        status = INPUT_ERROR;
        goto GT_CLOSE_FILE;
    }

    /* Read all samples */
    /* Note: This implementation discards one or two values if the EOF is reached and the real part is read already. */
    for(u64 idx = 0; (idx < *sampleCount); idx++)
    {
        double real, imaginary;
        int cnt = -1;
        cnt = fread(&real, sizeof(double), 1, file);
        if(cnt == EOF)
        {
            status = INPUT_ERROR;
            goto GT_CLOSE_FILE;
        }
        else if(cnt > 1)
        {
            status = INPUT_ERROR;
            goto GT_CLOSE_FILE;
        }
        cnt = fread(&imaginary, sizeof(double), 1, file);
        if(cnt == EOF)
        {
            status = INPUT_ERROR;
            goto GT_CLOSE_FILE;
        }
        else if(cnt > 1)
        {
            status = INPUT_ERROR;
            goto GT_CLOSE_FILE;
        }
        (*samples)[idx] = real + imaginary * I;
    }

    status = INPUT_SUCCESS;

    GT_CLOSE_FILE:
    fclose(file);
    return status;
}

input_status Input_writeFile(char* fileNameAndPath, u16 sampleCount, double complex* frequencyBins)
{
    int cnt = -1;
    input_status status = INPUT_UNDEFINED;
    FILE* file = fopen(fileNameAndPath, "wb");
    if(file == NULL)
    {
        status = INPUT_ERROR;
        goto GT_CLOSE_FILE;
    }

    cnt = fwrite(&sampleCount, sizeof(u16), 1, file);
    if(cnt != 1)
    {
        status = INPUT_ERROR;
        goto GT_CLOSE_FILE;
    }

    for(int n = 0; n < sampleCount; n++)
    {
        double realPart = creal(frequencyBins[n]);
        cnt = fwrite(&realPart, sizeof(double), 1, file);
        if(cnt != 1)
        {
            status = INPUT_ERROR;
            goto GT_CLOSE_FILE;
        }
        double imagPart = cimag(frequencyBins[n]);
        cnt = fwrite(&imagPart, sizeof(double), 1, file);
        if(cnt != 1)
        {
            status = INPUT_ERROR;
            goto GT_CLOSE_FILE;
        }
    }

    status = INPUT_SUCCESS;

    GT_CLOSE_FILE:
    fclose(file);
    return status;
}