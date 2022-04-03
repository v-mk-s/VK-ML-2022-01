// author : v - mk - s | copyright 2022

#include <stdio.h>
#include <stdlib.h>

#include "interface_main.h"
#include "processing_sequential.h"

int main(int argc, char *argv[])
{
    int c = 0;

    while (c != EXIT)
    {
        printf("HW2 sequential & parallel processing\n");
        printf("\t#1) Run processing sequential\n");
        printf("\t#2) Run processing parallel\n");
        printf("\t#3) Generate data file (sequence)\n");
        printf("\t#4) Exit\n");
        printf("Action number: ");

        if (scanf("%d", &c) == 0)
        {
            printf("Error! Wrong number.\nExit.\n");
            return ERROR_DEFAULT;
        }

        switch (c)
        {
        case SEQUENTIAL:
            call_sequential_processing();
            break;
        case PARALLEL:
            // IN WORK
            break;
        case FILE_GENERATION:
            call_sequence_gen(stdin);
            break;
        case EXIT:
            break;
        default:
            printf("Wrong action!\nExit.\n");
            break;
        }
    }

    return OK;
}
