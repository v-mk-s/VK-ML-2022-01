// author : v - mk - s | copyright 2022

#include <gtest/gtest.h>

extern "C"
{
#include "interface_main.h"
#include "processing_sequential.h"
}

TEST(InterfaceMain, TestProcessingSequential)
{
    char string1[] = "q\"aQC\"B\"Y\"\"Y1\"B\"D\"A12345abc#\0                         ";
    char *array1 = (char *)malloc(30 * sizeof(char));
    for (int i = 0; i < 30; ++i)
    {
        array1[i] = string1[i];
    }
    EXPECT_EQ(sequential_processing(array1), 2);

    char str2[] = "Abcdeabcde\"Abcdea\"bcdeAbcdeabcde\"AbcdeabcdeAbcdeabcde\0                ";
    char *arr2 = (char *)malloc(55 * sizeof(char));
    for (int i = 0; i < 55; ++i)
    {
        arr2[i] = str2[i];
    }
    EXPECT_EQ(sequential_processing(arr2), 6);
}

TEST(InterfaceMain, TestSequenceGeneration) {
    EXPECT_EQ(sequence_gen(20, 3, 2), 2);
}

TEST(InterfaceMain, TestInterface)
{
    EXPECT_EQ(delete_sequence(NULL), ERROR_DEFAULT);

    EXPECT_EQ(sequence_gen(20, 3, 2), 2);
}

TEST(SequentialProcessing, TestProcessingSequentialFunctions)
{
    EXPECT_EQ(delete_Extractor(NULL), ERROR_NOT_ALLOCATED);
}
