// author : v - mk - s | copyright 2022

#include "processing_sequential.h"

#include <stdio.h>
#include <stdlib.h>

// finding max quote length
int sequential_processing(char *seq)
{
    Extractor *obj = NULL;
    obj = init_Extractor(seq);
    if (!obj)
    {
        return ERROR_NOT_ALLOCATED;
    }

    if (write_in_Extractor(obj))
    {
        return ERROR_REALLOCATION;
    }

    int max_len = 0;
    max_len = get_max_quote_length(obj);

    // print_info_Extractor(obj);

    delete_Extractor(obj);

    return max_len;
}

// debug info
int print_info_Extractor(Extractor *obj)
{
    if (obj)
    {
    printf("########################\n");

        printf("max length = %d\n", obj->max_len);
        printf("arr_size = %d\n", obj->arr_size);
        printf("max_size = %d\n", obj->max_size);

        return OK;
    }

    return ERROR_DEFAULT;
}

// get max quote length
int get_max_quote_length(Extractor *obj)
{
    return obj->max_len;
}

// Initialize Extractor structure
Extractor *init_Extractor(char *seq)
{
    Extractor *obj = NULL;

    obj = malloc(sizeof(Extractor));
    if (!obj)
    {
        delete_Extractor(obj);
        return NULL;
    }
    obj->arr = NULL;
    obj->max_len = 0;
    obj->arr_size = 0;
    obj->max_size = ADD_BLOCK_SIZE;

    obj->arr = seq;

    return obj;
}

// calculate length of the most long quote in that block
int write_in_Extractor(Extractor *obj)
{
    char c = '\0';

    // int max_start = 0;
    // int max_end = 0;
    int max_len = 0;

    // int cur_start = 0;
    // int cur_end = 0;
    int cur_len = 0;

    bool first_quote = false;

    for (int i = 0; obj->arr[i] != '\0';)
    {
        c = obj->arr[i];

        if (first_quote) {
            if (c != '\"') {
                ++cur_len;
            } else {
                first_quote = false;
                if (cur_len > max_len) {
                    max_len = cur_len;
                }
            }
        } else if (c == '\"') {
            first_quote = true;
        }
        ++i;
    }

        // print_info_Extractor(obj);
    obj->arr_size = i;
    obj->max_len = max_len;


    return OK;
}

// delete Extractor structure
int delete_Extractor(Extractor *obj)
{
    if (!obj)
    {
        return ERROR_NOT_ALLOCATED;
    }

    if (obj->arr)
    {
        free(obj->arr);
        obj->arr = NULL;
    }

    free(obj);
    obj = NULL;

    return OK;
}
