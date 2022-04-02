// author : v - mk - s | copyright 2022

#include <gtest/gtest.h>

extern "C"
{
#include "interface_main.h"
#include "processing_sequential.h"
}

TEST(Interface, test_consistent_alg) {
    char str1[] = "EECCAABBDEEDDDCCDEE";
    char *arr1 = (char *)malloc(20 * sizeof(char));
    for (int i = 0; i < 20; ++i)
    {
        arr1[i] = str1[i];
    }
    EXPECT_EQ(sequential_processing(arr1), 2);

    char str2[] = "BBEEAADDDDBBDDDDDDDDAAAAABBBBBBEEEEEEAADDDDDEEEBBBBBCCEEECEEEEEEEEEEBBBBBBBCCCCCCBBBBBBDDCCCCCCDDBAAAAAEEEAAAAAAAAAADDDDDBBBBBBBBBBEEEAAAAAAAACCCCCCCCCDDDDDDDDDEEEEEEEEEAAAABBBBBBDDEEEEEEEEEBBBBBBBBB";
    char *arr2 = (char *)malloc(200 * sizeof(char));
    for (int i = 0; i < 200; ++i)
    {
        arr2[i] = str2[i];
    }
    EXPECT_EQ(sequential_processing(arr2), 2);
}

TEST(Interface, test_sequence_gen) {
    EXPECT_EQ(sequence_gen(20, 3, 2), 2);
}

TEST(Interface, test_interface) {
    EXPECT_EQ(delete_sequence(NULL), 1);
    // FILE* fp = NULL;
    // char str1[] = "20 3 2\n";
    // fp = fmemopen(str1, 8, "r");
    // EXPECT_EQ(call_sequence_gen(fp), 1);

    EXPECT_EQ(sequence_gen(20, 3, 2), 2);
    // EXPECT_EQ(call_sequential_processing(), 2);
    // fclose(fp);
}

TEST(sequential_processing, consistent_alg_functions) {
    EXPECT_EQ(delete_RLE(NULL), NOT_ALLOCATED);
    EXPECT_EQ(increase_arr_size(NULL), POINTER_ERROR);
}
