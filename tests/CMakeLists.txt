# cmake_minimum_required(VERSION 3.14)
# project(test_mail)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

# file(GLOB SOURCES *.cpp)

# find_package(GTest REQUIRED)

# add_executable(${PROJECT_NAME} ${SOURCES})
# target_include_directories(${PROJECT_NAME} PUBLIC ${MAIL_LIB_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} ${MAIL_LIB_LIBRARIES} GTest::GTest gtest_main)

cmake_minimum_required(VERSION 3.14.0)
project(test_mail)

set(TESTS_MAIL_EXECUTABLE)
set(TESTS_MAIL_INCLUDE_DIRS)

file(GLOB SOURCES *.cc)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_GMOCK "Do you want to build Gmock?" OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${MAIL_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${MAIL_LIB_LIBRARIES} gtest_main)

set(TESTS_MAIL_EXECUTABLE ${PROJECT_NAME} PARENT_SCOPE)
set(TESTS_MAIL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

# Add valgrind to make target
add_custom_target(
        tests_with_valgrind
        COMMAND make
        -j8
        &&
        valgrind
        --tool=memcheck
        --leak-check=yes
        ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME}
)