# author: v-mk-s | copyright 2022

#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN clang-format"
check_log "clang-format -style=google -i **/*.c **/*.h" "\(information\)"
print_header "SUCCESSFULLY DONE clang-format"
print_header "SUCCESS 1/3"

print_header "RUN cppcheck"
check_log "cppcheck **/*.c IT--enable=all --inconclusive --error-exitcode=1 -Iprocessing_sequential -Iinterface -Iprocessing_parallel --suppress=missingIncludeSystem" "\(information\)"
print_header "SUCCESSFULLY DONE cppcheck"
print_header "SUCCESS 2/3"

print_header "RUN cpplint"
check_log "cpplint --extensions=c **/*.c" "ERROR! Cannot be opened for reading (r)."
print_header "SUCCESSFULLY DONE cpplint"
print_header "SUCCESS 3/3"

print_header "ALL WAS SUCCESSFULL"
