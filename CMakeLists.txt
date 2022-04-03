# author: v-mk-s | copyright 2022

cmake_minimum_required(VERSION 3.0.0)
project(project)

add_executable(${PROJECT_NAME} src/main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")

add_subdirectory(processing_sequential)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROCESSING_SEQUENTIAL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROCESSING_SEQUENTIAL_LIBRARIES})

add_subdirectory(interface_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_MAIN_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${INTERFACE_MAIN_LIBRARIES})

add_subdirectory(tests)
