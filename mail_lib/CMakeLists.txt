cmake_minimum_required(VERSION 3.0.0)
project(mail_lib)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -ggdb3")

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(MAIL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(MAIL_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


################ вариант 2, не работает( #######################
# cmake_minimum_required(VERSION 3.0.0)
# project(mail_lib)

# set(MAIL_LIB_LIBRARIES)
# set(MAIL_LIB_INCLUDE_DIRS)

# file(GLOB SOURCES *.c)
# file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# add_library(${PROJECT_NAME} STATIC ${SOURCES})

# set(MAIL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
# set(MAIL_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


################ вариант 3, не работает( #######################
# cmake_minimum_required(VERSION 3.0.0)
# project(mail_lib)

# set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

# file(GLOB SOURCES *.c)
# file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# add_library(${PROJECT_NAME} ${SOURCES})

# set(MAIL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
# set(MAIL_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)