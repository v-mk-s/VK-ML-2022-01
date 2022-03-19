cmake_minimum_required(VERSION 3.0.0)
project(mail)

add_subdirectory(mail_lib)

message("MAIL_LIB_INCLUDE_DIRS = ${MAIL_LIB_INCLUDE_DIRS}")
message("MAIL_LIB_LIBRARIES = ${MAIL_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${MAIL_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MAIL_LIB_LIBRARIES})

add_subdirectory(tests)
