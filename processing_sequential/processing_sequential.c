// author : v - mk - s | copyright 2022

#include "processing_sequential.h"

#include <stdio.h>
#include <stdlib.h>

// Find most frequently appearing length
int sequential_processing(char *seq)
{
    RLE *obj = NULL;
    obj = init_RLE(seq);
    if (!obj)
    {
        return NOT_ALLOCATED;
    }

    if (fill_RLE(obj))
    {
        return REALLOCATION_ERROR;
    }

    int max = 0;
    max = get_max_occurance_length(obj);

    // print_info(obj);

    delete_RLE(obj);

    return max;
}

// Debug information
void print_info(RLE *obj)
{
    printf("___________\n");
    for (int i = 0; i < obj->arr_size; ++i)
    {
        printf("[%d]: ", i);
        printf("length - %d, ", obj->length[i]);
        printf("occurs - %d times, ", obj->occurancies[i]);
        printf("representer - %c\n", obj->representer[i]);
    }
    printf("amount of series - %d\n", obj->arr_size);
    // printf("sequence - %s\n", obj->arr);
    return;
}

// Get length which occured most often
int get_max_occurance_length(RLE *obj)
{
    int max = obj->occurancies[obj->arr_size - 1];
    int index = 0;

    for (int i = obj->arr_size - 1; i >= 0; --i)
    {
        if (max < obj->occurancies[i])
        {
            max = obj->occurancies[i];
            index = i;
        }
    }

    // printf("Most frequently occuring length - %d\n", obj->length[index]);
    // printf("It occurs %d times\n", obj->occurancies[index]);
    // printf("Representer - %c\n", obj->representer[index]);
    return obj->length[index];
}

// Initialize RLE structure
RLE *init_RLE(char *seq)
{
    RLE *obj = NULL;

    obj = malloc(sizeof(RLE));
    if (!obj)
    {
        delete_RLE(obj);
        return NULL;
    }
    obj->arr = NULL;
    obj->representer = NULL;
    obj->length = NULL;
    obj->occurancies = NULL;
    obj->arr_size = 0;
    obj->current_length = 0;
    obj->max_size = BLOCK_SIZE;

    obj->arr = seq;

    obj->occurancies = malloc(obj->max_size * sizeof(int));
    if (!obj->occurancies)
    {
        delete_RLE(obj);
        return NULL;
    }

    obj->length = malloc(obj->max_size * sizeof(int));
    if (!obj->length)
    {
        delete_RLE(obj);
        return NULL;
    }

    obj->representer = malloc(obj->max_size * sizeof(char));
    if (!obj->representer)
    {
        delete_RLE(obj);
        return NULL;
    }

    for (int i = 0; i < obj->max_size; ++i)
    {
        obj->occurancies[i] = 0;
        obj->length[i] = 0;
        obj->representer[i] = '\0';
    }

    return obj;
}

// Calculate length occurancies and how often they appear
int fill_RLE(RLE *obj)
{
    char c = '\0';

    for (int i = 0; obj->arr[i] != '\0';)
    {
        c = obj->arr[i];
        while (c == obj->arr[i])
        {
            ++obj->current_length;
            ++i;
        }

        int length_index =
            length_checked(obj->length, obj->current_length, obj->arr_size);
        if (length_index >= 0)
        {
            obj->occurancies[length_index] += 1;
            obj->representer[length_index] = obj->arr[i - 1];
        }
        else
        {
            if (obj->arr_size == obj->max_size)
            {
                if (increase_arr_size(obj))
                {
                    return REALLOCATION_ERROR;
                }
            }
            obj->representer[obj->arr_size] = obj->arr[i - 1];
            obj->occurancies[obj->arr_size] += 1;
            obj->length[obj->arr_size] = obj->current_length;
            ++obj->arr_size;
        }

        // print_info(obj);
        obj->current_length = 0;
    }

    return OK;
}

// Increase size of obj->length and obj->occurancies if it is full by BLOCK_SIZE
int increase_arr_size(RLE *obj)
{
    int *tmp_i = NULL;
    char *tmp_c = NULL;

    if (!obj)
    {
        return POINTER_ERROR;
    }

    obj->max_size = obj->max_size + BLOCK_SIZE;

    tmp_i = obj->length;
    obj->length = NULL;
    obj->length = malloc(obj->max_size * sizeof(int));
    if (!obj->length)
    {
        return NOT_ALLOCATED;
    }
    for (int i = 0; i < obj->arr_size; ++i)
    {
        obj->length[i] = tmp_i[i];
    }
    free(tmp_i);

    tmp_i = obj->occurancies;
    obj->occurancies = NULL;
    obj->occurancies = malloc(obj->max_size * sizeof(int));
    if (!obj->occurancies)
    {
        return NOT_ALLOCATED;
    }
    for (int i = 0; i < obj->arr_size; ++i)
    {
        obj->occurancies[i] = tmp_i[i];
    }
    free(tmp_i);

    tmp_c = obj->representer;
    obj->representer = NULL;
    obj->representer = malloc(obj->max_size * sizeof(int));
    if (!obj->representer)
    {
        return NOT_ALLOCATED;
    }
    for (int i = 0; i < obj->arr_size; ++i)
    {
        obj->representer[i] = tmp_c[i];
    }
    free(tmp_c);

    for (int i = obj->arr_size; i < obj->max_size; ++i)
    {
        obj->length[i] = 0;
        obj->occurancies[i] = 0;
    }

    return OK;
}

// Check if specific length has already appeared
// if YES return index in length[], else -1
int length_checked(int *length, int current_length, int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
    {
        if (length[i] == current_length)
        {
            return i;
        }
    }
    return -1;
}

// Delete allocated memory for RLE structure
int delete_RLE(RLE *obj)
{
    if (!obj)
    {
        return NOT_ALLOCATED;
    }

    if (obj->arr)
    {
        free(obj->arr);
        obj->arr = NULL;
    }
    if (obj->representer)
    {
        free(obj->representer);
        obj->representer = NULL;
    }
    if (obj->occurancies)
    {
        free(obj->occurancies);
        obj->occurancies = NULL;
    }
    if (obj->length)
    {
        free(obj->length);
        obj->length = NULL;
    }
    free(obj);
    obj = NULL;

    return OK;
}
