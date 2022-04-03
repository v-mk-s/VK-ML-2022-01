// author : v - mk - s | copyright 2022

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "interface_main.h"
#include "processing_sequential.h"

// make sequential processing
int call_sequential_processing()
{
    char *seq = read_from_file();
    clock_t start, stop;

    start = clock();
    int result = sequential_processing(seq);
    stop = clock();

    // printf("Sequential processing time = %lu\n", (stop - start));

    return result;
}

// make sequential generation
int call_sequence_gen(FILE *p_file)
{
    int array_size = 0;
    int length_max = 0;
    int length_quote = 0;

    printf("Enter size of array which will be generated:\n");
    if (fscanf(p_file, "%d", &array_size) == EOF)
    {
        printf("Error! Wrong array size\n");
        return ERROR_DEFAULT;
    }

    printf("Enter maximum length:\n");
    if (fscanf(p_file, "%d", &length_max) == EOF)
    {
        printf("Error! Wrong max length\n");
        return ERROR_DEFAULT;
    }

    printf("Enter quote length:\n");
    if (fscanf(p_file, "%d", &length_quote) == EOF)
    {
        printf("Error! Wrong quote length\n");
        return ERROR_DEFAULT;
    }

    sequence_gen(array_size, length_max, length_quote);

    return OK;
}

/*
// make parallel processing
int call_parallel_processing() {
// void* library;
   char *seq = read_from_file();
   clock_t start, stop;

   start = clock();
   int result = parallel_processing(seq);
   stop = clock();

   printf("Parallel processing time = %lu\n", (stop - start));

   return result;
}
*/

char *read_from_file(void)
{
    FILE *p_file = NULL;
    p_file = fopen(FILENAME, "r");
    if (!p_file)
    {
        return NULL;
    }

    int array_size = 0;
    fseek(p_file, 0, SEEK_END);
    array_size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);

    char *seq = NULL;
    seq = malloc(array_size * sizeof(char));
    if (!seq)
    {
        fclose(p_file);
        return NULL;
    }

    while (fscanf(p_file, "%s", seq) != EOF)
    {
    }

    if (fclose(p_file) == 0)
    {
        return seq;
    }
    else
    {
        free(seq);
        return NULL;
    }
}
