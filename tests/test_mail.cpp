#include <gtest/gtest.h>

extern "C" {
    #include "mail.h"
}

TEST(return_pointer_to_struct, TestBasics) {
    EXPECT_EQ(1, fib(1));
    EXPECT_EQ(1, fib(2));
}

TEST(Fib, Test10) {
    EXPECT_EQ(55, fib(10));
}

#define GOOD 1
#define BAD 0

TEST(schedule_private_TESTS, AddBeginTime_TEST) {
  char input[] = "12 00\n1200\n12:00\nqwerty\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  time_t timer = 0;

  EXPECT_EQ(GOOD, AddBeginTime(stream, &timer));
  EXPECT_EQ(BAD, AddBeginTime(stream, &timer));
  EXPECT_EQ(BAD, AddBeginTime(stream, &timer));
  EXPECT_EQ(BAD, AddBeginTime(stream, &timer));

  fclose(stream);
}

TEST(schedule_private_TESTS, AddLessonType_TEST) {
  char input[] = "2\n0\nqwerty\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  LessonType type = lecture;

  EXPECT_EQ(GOOD, AddLessonType(stream, &type));
  EXPECT_EQ(BAD, AddLessonType(stream, &type));
  EXPECT_EQ(BAD, AddLessonType(stream, &type));

  fclose(stream);
}

TEST(schedule_private_TESTS, AddDuration_TEST) {
  char input[] = "5\n30\nqwerty\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  time_t timer = 0;

  EXPECT_EQ(GOOD, AddDuration(stream, &timer));
  EXPECT_EQ(BAD, AddDuration(stream, &timer));
  EXPECT_EQ(BAD, AddDuration(stream, &timer));

  fclose(stream);
}

TEST(schedule_private_TESTS, AddSubject_TEST) {
  char input[] = "Ababab Ababab\nTurututu Turututu\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  char* str = NULL;

  EXPECT_EQ(GOOD, AddSubject(stream, &str));
  EXPECT_EQ(GOOD, AddSubject(stream, &str));
  EXPECT_EQ(BAD, AddSubject(stream, &str));

  free(str);
  fclose(stream);
}

TEST(schedule_private_TESTS, AddTeacher_TEST) {
  char input[] = "Ababab Ababab\nTurututu Turututu\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  char* str = NULL;

  EXPECT_EQ(GOOD, AddTeacher(stream, &str));
  EXPECT_EQ(GOOD, AddTeacher(stream, &str));
  EXPECT_EQ(BAD, AddTeacher(stream, &str));

  free(str);
  fclose(stream);
}

TEST(schedule_private_TESTS, AddClassroom_TEST) {
  char input[] = "385\n221m\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  char* str = NULL;

  EXPECT_EQ(GOOD, AddClassroom(stream, &str));
  EXPECT_EQ(GOOD, AddClassroom(stream, &str));
  EXPECT_EQ(BAD, AddClassroom(stream, &str));

  free(str);
  fclose(stream);
}

TEST(schedule_private_TESTS, GetDay_TEST) {
  char input[] = "2\n12\nqwerty\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  int num = 0;

  EXPECT_EQ(GOOD, GetDay(stream, &num));
  EXPECT_EQ(BAD, GetDay(stream, &num));
  EXPECT_EQ(BAD, GetDay(stream, &num));

  fclose(stream);
}

TEST(schedule_private_TESTS, GetYear_TEST) {
  char input[] = "2\n12\nqwerty\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  int num = 0;

  EXPECT_EQ(GOOD, GetYear(stream, &num));
  EXPECT_EQ(BAD, GetYear(stream, &num));
  EXPECT_EQ(BAD, GetYear(stream, &num));

  fclose(stream);
}

TEST(schedule_private_TESTS, GetGroup_TEST) {
  char input[] = "1\n12\nqwerty\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  int num = 0;

  EXPECT_EQ(GOOD, GetGroup(stream, &num));
  EXPECT_EQ(BAD, GetGroup(stream, &num));
  EXPECT_EQ(BAD, GetGroup(stream, &num));

  fclose(stream);
}

TEST(schedule_private_TESTS, AddLesson_TEST) {
  char input[] = "12 00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n2\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  Lessons lesson = {5, 0, NULL};
  EXPECT_EQ(BAD, AddLesson(stream, &lesson));
  fclose(stream);

  input[10] = '\n';
  lesson.use_size = 0;
  stream = fmemopen(input, strlen(input), "r");
  EXPECT_EQ(BAD, AddLesson(stream, &lesson));

  fclose(stream);
}

TEST(schedule_TESTS, CreateSchedule_TEST) {
  char input1[] = "12\n12 00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n2\n0\n";
  FILE* stream1 = fmemopen(input1, strlen(input1), "r");
  Lessons* schedule = NULL;

  EXPECT_EQ(BAD, CreateSchedule(stream1, &schedule));
  ASSERT_NO_THROW(DeleteSchedule(&schedule));

  char input2[] = "1\n12:00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n2\n0\n";
  FILE* stream2 = fmemopen(input2, strlen(input2), "r");

  EXPECT_EQ(BAD, CreateSchedule(stream2, &schedule));
  ASSERT_NO_THROW(DeleteSchedule(&schedule));

  char input3[] = "1\n12 00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n2\n";
  FILE* stream3 = fmemopen(input3, strlen(input3), "r");

  EXPECT_EQ(BAD, CreateSchedule(stream3, &schedule));
  ASSERT_NO_THROW(DeleteSchedule(&schedule));

  char input4[] = "1\n12 00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n2\nqwerty\n";
  FILE* stream4 = fmemopen(input4, strlen(input4), "r");

  EXPECT_EQ(BAD, CreateSchedule(stream4, &schedule));
  ASSERT_NO_THROW(DeleteSchedule(&schedule));

  fclose(stream1);
  fclose(stream2);
  fclose(stream3);
  fclose(stream4);
}

TEST(schedule_TESTS, PrintSchedule_TEST) {
  char input1[] = "1\n12 00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n1\n0\n";
  FILE* stream1 = fmemopen(input1, strlen(input1), "r");
  Lessons* schedule = NULL;

  EXPECT_EQ(GOOD, CreateSchedule(stream1, &schedule));

  char input2[] = "0\n";
  FILE* stream2 = fmemopen(input2, strlen(input2), "r");

  EXPECT_EQ(BAD, PrintSchedule(stream2, schedule));

  char input3[] = "1\n0\n";
  FILE* stream3 = fmemopen(input3, strlen(input3), "r");

  EXPECT_EQ(BAD, PrintSchedule(stream3, schedule));

  char input4[] = "1\n1\n0\n";
  FILE* stream4 = fmemopen(input4, strlen(input4), "r");

  EXPECT_EQ(BAD, PrintSchedule(stream4, schedule));

  char input5[] = "1\n1\n1\n";
  FILE* stream5 = fmemopen(input5, strlen(input5), "r");
  memset(&schedule[0].lessons[0].type, 0, sizeof(schedule[0].lessons[0].type));
  EXPECT_EQ(BAD, PrintSchedule(stream5, schedule));
  ASSERT_NO_THROW(DeleteSchedule(&schedule));

  fclose(stream1);
  fclose(stream2);
  fclose(stream3);
  fclose(stream4);
  fclose(stream5);
}

TEST(schedule_private_TESTS, PrintLesson_TEST) {
  char input[] = "12 00\n1\n3\nMath\nVasileva D.S.\n904l\n1\n1\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  Lessons lesson = {0, 0, NULL};
  lesson.lessons = (Lesson*)calloc(1, sizeof(Lesson));
  EXPECT_EQ(BAD, PrintLesson(lesson.lessons));
  free(lesson.lessons);
  fclose(stream);
}

TEST(MAIN_TESTS, RIGHT_INPUT_TEST) {
  char input[] =
      "1\n15 00\n2\n4\nC++\nZaycev V.K.\n666l\n1\n2\n1\n"
      "1\n12 00\n1\n2\nMath\nVasileva D.S.\n904l\n1\n2\n1\n"
      "1\n10 00\n1\n2\nMath\nVasileva D.S.\n904l\n1\n2\n0\n"
      "1\n1\n2\n";
  FILE* stream = fmemopen(input, strlen(input), "r");
  Lessons* schedule = NULL;

  EXPECT_EQ(GOOD, CreateSchedule(stream, &schedule));
  EXPECT_EQ(GOOD, PrintSchedule(stream, schedule));
  ASSERT_NO_THROW(DeleteSchedule(&schedule));

  fclose(stream);
}
