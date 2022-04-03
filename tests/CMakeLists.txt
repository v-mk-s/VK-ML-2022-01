# author: v-mk-s | copyright 2022

cmake_minimum_required(VERSION 3.0.0)
project(tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")

file(GLOB SOURCES *.cpp)

find_package(GTest CONFIG REQUIRED) 

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_MAIN_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${INTERFACE_MAIN_LIBRARIES} GTest::gtest_main)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROCESSING_SEQUENTIAL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PROCESSING_SEQUENTIAL_LIBRARIES} GTest::gtest_main)
