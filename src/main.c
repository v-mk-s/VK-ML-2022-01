// author : v - mk - s | copyright 2022

#include <stdio.h>
#include <stdlib.h>

#include "interface_main.h"

enum action_type
{
    CONSISTENT = 1,
    PARALLEL,
    GEN_FILE,
    EXIT
};

int main(int argc, char *argv[])
{
    int c = 0;

    while (c != EXIT)
    {
        printf("Choose action:\n");
        printf("\t1 - Run consistent algorithm\n");
        printf("\t2 - Run parallel algorithm\n");
        printf("\t3 - Generate file with sequence\n");
        printf("\t4 - Exit\n");
        printf("Action: ");

        if (scanf("%d", &c) == 0)
        {
            printf("Error: number must be written.\n");
            return FAIL;
        }

        switch (c)
        {
        case CONSISTENT:
            call_sequential_processing();
            break;
        case PARALLEL:
            break;
        case GEN_FILE:
            call_sequence_gen(stdin);
            break;
        case EXIT:
            break;
        default:
            printf("Wrong action\n");
            break;
        }
    }

    return OK;
}
