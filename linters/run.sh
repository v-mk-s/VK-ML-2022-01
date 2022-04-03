#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

# function check_log() {
#     LOG=$( { ${1}; } 2>&1 )
#     STATUS=$?
#     echo "$LOG"
#     if echo "$LOG" | grep -q -E "${2}"
#     then
#         exit 1
#     fi

#     if [ $STATUS -ne 0 ]
#     then
#         exit $STATUS
#     fi
# }

print_header "RUN clang-format"
clang-tidy project/src/* project/include/* -warnings-as-errors=* -extra-arg=-std=c99 -- -Iproject/include
print_header "SUCCESSFULLY DONE clang-format"
print_header "SUCCESS 1/3"

print_header "RUN cppcheck"
cppcheck project --enable=all --inconclusive --error-exitcode=1 -I project/include -I project/tests/include --suppress=missingIncludeSystem
print_header "SUCCESSFULLY DONE cppcheck"
print_header "SUCCESS 2/3"

print_header "RUN cpplint"
python3 ./linters/cpplint/cpplint.py --extensions=c project/include/* project/src/*
print_header "SUCCESSFULLY DONE cpplint"
print_header "SUCCESS 3/3"

print_header "ALL WAS SUCCESSFULL"
