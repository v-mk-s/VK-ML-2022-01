#include <gtest/gtest.h>

extern "C" {
    #include "mail.h"
}

#define OK_TEST true
#define BAD false

TEST(CreateMail, TestCreateMail) {
    char input1[] = "t.e_s-t@mail.ru\n";
    FILE* stream1 = fmemopen(input1, strlen(input1), "r");
    Mail *new_mail = NULL;
    EXPECT_EQ(OK_TEST, create_mail_pointer_to_struct(stream1, &new_mail));
    ASSERT_NO_THROW(delete_mail(&new_mail));
    fclose(stream1);

    char input2[] = "test@mail.r1u\n";
    FILE* stream2 = fmemopen(input2, strlen(input2), "r");
    EXPECT_EQ(BAD, create_mail_pointer_to_struct(stream2, &new_mail));
    ASSERT_NO_THROW(delete_mail(&new_mail));
    fclose(stream2);

    char input3[] = "test@ma2il.ru\n";
    FILE* stream3 = fmemopen(input3, strlen(input3), "r");
    EXPECT_EQ(BAD, create_mail_pointer_to_struct(stream3, &new_mail));
    ASSERT_NO_THROW(delete_mail(&new_mail));
    fclose(stream3);

    char input4[] = "test@ma.il.ru\n";
    FILE* stream4 = fmemopen(input4, strlen(input4), "r");
    EXPECT_EQ(BAD, create_mail_pointer_to_struct(stream4, &new_mail));
    ASSERT_NO_THROW(delete_mail(&new_mail));
    fclose(stream4);
}

TEST(DeleteMail, TestDeleteMail) {
    char input1[] = "t.e_s-t@mail.ru\n";
    FILE* stream1 = fmemopen(input1, strlen(input1), "r");
    Mail *new_mail = NULL;
    ASSERT_NO_THROW(create_mail_pointer_to_struct(stream1, &new_mail));
    EXPECT_EQ(OK_TEST, delete_mail(&new_mail));
    fclose(stream1);
}

TEST(PrintMail, PrintMail) {
    char input1[] = "t.e_s-t@mail.ru\n";
    FILE* stream1 = fmemopen(input1, strlen(input1), "r");
    Mail *new_mail = NULL;
    ASSERT_NO_THROW(create_mail_pointer_to_struct(stream1, &new_mail));
    EXPECT_EQ(OK_TEST, print_mail(new_mail));
    ASSERT_NO_THROW(delete_mail(&new_mail));
    fclose(stream1);

    char input2[] = "test@ma2il.ru\n";
    FILE* stream2 = fmemopen(input2, strlen(input2), "r");
    ASSERT_NO_THROW(create_mail_pointer_to_struct(stream2, &new_mail));
    EXPECT_EQ(BAD, print_mail(new_mail));
    ASSERT_NO_THROW(delete_mail(&new_mail));
    fclose(stream2);
}
