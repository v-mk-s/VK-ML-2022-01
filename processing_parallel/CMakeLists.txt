# author: v-mk-s | copyright 2022

cmake_minimum_required(VERSION 3.0.0)
project(project_processing_parallel)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

# target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_MAIN_INCLUDE_DIRS} PARENT_SCOPE)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${INTERFACE_MAIN_LIBRARIES})

set(PROCESSING_PARALLEL_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(PROCESSING_PARALLEL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
