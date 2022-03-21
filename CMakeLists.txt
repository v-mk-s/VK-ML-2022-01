cmake_minimum_required(VERSION 3.0.0)
project(mail-hw-1)

# option(BUILD_TESTS "Do you want to build tests?" OFF)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# if (BUILD_TESTS)
#   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
#   set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -fprofile-arcs -ftest-coverage -fPIC -O0")
#   set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -Werror -fprofile-arcs -ftest-coverage -fPIC -O0")
# else()
#   set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -O2")
#   set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -O2")
# endif()

add_subdirectory(mail_lib)

message("MAIL_LIB_LIBRARIES = ${MAIL_LIB_LIBRARIES}")
message("MAIL_LIB_INCLUDE_DIRS = ${MAIL_LIB_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} main.c)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
target_include_directories(${PROJECT_NAME} PUBLIC ${MAIL_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MAIL_LIB_LIBRARIES})

add_subdirectory(tests)


################ вариант 2, не работает( #######################
# cmake_minimum_required(VERSION 3.0.0)
# project(mail-hw-1)

# option(BUILD_TESTS "Do you want to build tests?" OFF)

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_CXX_STANDARD 11)

# if (BUILD_TESTS)
#   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
#   set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -fprofile-arcs -ftest-coverage -fPIC -O0")
#   set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wpedantic -Wextra -Werror -fprofile-arcs -ftest-coverage -fPIC -O0")
# else()
#   set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -O2")
#   set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -O2")
# endif()

# add_subdirectory(mail_lib)

# add_executable(${PROJECT_NAME} main.c)

# target_include_directories(${PROJECT_NAME} PUBLIC ${MAIL_LIB_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${MAIL_LIB_LIBRARIES})

# if (BUILD_TESTS)
#   add_subdirectory(tests)
# endif()

# # Add clang-tidy with clang-analyzer (scan-build)
# set(CMAKE_C_CLANG_TIDY 
#   clang-tidy-12;
#   -header-filter=.;
#   -warnings-as-errors=*;
#   -extra-arg=-std=c99;
#   -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)

# # Add clang-format-12 to make target
# add_custom_target(
#         clangformat
#         COMMAND clang-format-12
#         -style=Chromium
#         -n
#         --Werror
#         ${CMAKE_CURRENT_SOURCE_DIR}/*.c
#         ${MAIL_LIB_INCLUDE_DIRS}/*.c
#         ${MAIL_LIB_INCLUDE_DIRS}/*.h
#         ${TESTS_MAIL_INCLUDE_DIRS}/*.cc
# )


################ вариант 3, не работает( #######################

# cmake_minimum_required(VERSION 3.0.0)
# project(mail)

# add_subdirectory(mail_lib)

# message("MAIL_LIB_INCLUDE_DIRS = ${MAIL_LIB_INCLUDE_DIRS}")
# message("MAIL_LIB_LIBRARIES = ${MAIL_LIB_LIBRARIES}")

# add_executable(${PROJECT_NAME} main.c)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

# target_include_directories(${PROJECT_NAME} PUBLIC ${MAIL_LIB_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${MAIL_LIB_LIBRARIES})

# add_subdirectory(tests)

