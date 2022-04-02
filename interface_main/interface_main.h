// author : v - mk - s | copyright 2022

#ifndef INTERFACE_MAIN
#define INTERFACE_MAIN

#include <stdio.h>

#define OK 0
#define FAIL 1

#define ERROR_OPEN_FILE 4
#define ERROR_WRITE_DATA 5

#define FILENAME "sequence_one.txt"

typedef struct sequence
{
    char *array;
    int *qoute;
    int size;
} sequence;

char const * rand_array= {'A', '1', '\"'};

int call_parallel_processing();
int call_sequential_processing();
int call_sequence_gen(FILE *p_file);

int interface(int const);
char *read_from_file();

sequence *sequence_init(int const array_size, int const length_max);
char get_random_char();
int delete_sequence(sequence *obj);
int check_qoute(int *array, int const n, int const length_max);
void gen_quotes(sequence *seq, int const length);
int sequence_gen(int const array_size, int const length_max, int const n);
int write_data_to_file(char *sequence);

#endif  // INTERFACE_MAIN
