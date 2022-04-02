// author : v - mk - s | copyright 2022

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "interface_main.h"

// Check qoute: find max length of re("[A-Z]*")
int check_qoute(int *array, int const n, int const length_max)
{
    for (int i = 0; i < length_max; ++i)
    {
        if (i != n - 1)
        {
            if (array[n - 1] - array[i] <= 2)
            { // not enough series
                return OK;
            }
        }
    }
    return FAIL; // enough series
}

// generate quote of specific length
void gen_quotes(sequence *seq, int const length)
{
    char sym = get_random_char();
    if (seq->size > 0)
    {
        while ((sym = get_random_char()) == seq->array[seq->size - 1])
        {
        }
    }

    for (int i = 0; i < length; ++i)
    {
        seq->array[seq->size++] = sym;
    }
    return;
}

// save sequence (array) into file
int write_data_to_file(char *sequence)
{
    FILE *p_file = NULL;
    p_file = fopen(FILENAME, "w");
    if (!p_file)
    {
        return ERROR_OPEN_FILE;
    }

    if (fprintf(p_file, "%s", sequence) < 0)
    {
        fclose(p_file);
        return ERROR_WRITE_DATA;
    }

    fclose(p_file);
    return OK;
}

// sequence initialization
sequence *sequence_init(int const array_size, int const length_max)
{
    sequence *obj = malloc(sizeof(sequence));
    if (!obj)
    {
        return NULL;
    }
    obj->array = NULL;
    obj->qoute = NULL;

    obj->array = malloc(array_size * sizeof(char));
    if (!obj->array)
    {
        delete_sequence(obj);
        return NULL;
    }
    obj->qoute = malloc(length_max * sizeof(int));
    if (!obj->qoute)
    {
        delete_sequence(obj);
        return NULL;
    }
    for (int i = 0; i < length_max; ++i)
    {
        obj->qoute[i] = 0;
    }
    obj->size = 0;

    return obj;
}

// make sequence generation
int sequence_gen(int const array_size, int const length_max, int const n)
{
    srandom(time(NULL));

    sequence *seq = sequence_init(array_size, length_max);
    if (!seq)
    {
        return FAIL;
    }

    while (seq->size < array_size)
    {
        if (check_qoute(seq->qoute, n, length_max))
        {
            int random_length = random() % length_max + 1;
            ++seq->qoute[random_length - 1];
            gen_quotes(seq, random_length);
        }
        else
        {
            ++seq->qoute[n - 1];
            gen_quotes(seq, n);
        }

        if (array_size - seq->size <= length_max)
        {
            ++seq->qoute[array_size - seq->size - 2];

            gen_quotes(seq, array_size - seq->size - 1);

            seq->array[seq->size++] = '\0';
        }
    }

    write_data_to_file(seq->array);

    delete_sequence(seq);

    return n;
}

// Generate random specific char
char get_random_char() { return rand_array[random() % 3]; }

// Free allocated memory
int delete_sequence(sequence *obj)
{
    if (!obj)
    {
        return FAIL;
    }

    if (obj->array)
    {
        free(obj->array);
        obj->array = NULL;
    }

    if (obj->qoute)
    {
        free(obj->qoute);
        obj->qoute = NULL;
    }

    free(obj);
    obj = NULL;

    return OK;
}
