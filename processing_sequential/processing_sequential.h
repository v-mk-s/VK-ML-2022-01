// author : v - mk - s | copyright 2022

#ifndef PROCESSING_SEQUENTIAL
#define PROCESSING_SEQUENTIAL

// Error codes
#define NOT_ALLOCATED 1
#define REALLOCATION_ERROR 2
#define POINTER_ERROR 3

#define BLOCK_SIZE 8

typedef struct
{
    char *arr;
    char *representer;
    int *occurancies;
    int *length;
    int current_length;
    int arr_size;
    int max_size;
} RLE;

int sequential_processing(char *);
RLE *init_RLE(char *);
int delete_RLE(RLE *);
int fill_RLE(RLE *);
int length_checked(int[], int, int);
int increase_arr_size(RLE *);
int get_max_occurance_length(RLE *);
void print_info(RLE *);

#endif  // PROCESSING_SEQUENTIAL
