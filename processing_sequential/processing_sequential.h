// author : v - mk - s | copyright 2022

#ifndef PROCESSING_SEQUENTIAL
#define PROCESSING_SEQUENTIAL

#include <stdbool.h>

#define OK 0
#define ERROR_DEFAULT 10

#define ERROR_NOT_ALLOCATED 1
#define ERROR_REALLOCATION 2
#define ERROR_WRONG_POINTER 3

#define ADD_BLOCK_SIZE 8

typedef struct
{
    char *arr;
    int max_len;
    int arr_size;
    int max_size;
} Extractor;

int sequential_processing(char *seq);
Extractor *init_Extractor(char *seq);
int delete_Extractor(Extractor *obj);
int write_in_Extractor(Extractor *obj);
int get_max_quote_length(Extractor *obj);
int print_info_Extractor(Extractor *obj);

#endif  // PROCESSING_SEQUENTIAL
