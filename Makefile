# author: v-mk-s | copyright 2022

build_all:
	cmake -B build; cmake --build build

clean:
	rm -rf build

build:
	cmake -B build; cmake --build build

rebuild:
	make clean && make build_all

run:	./build/main
	./build/main $(n)

check:
	./linters/run.sh

test:
	./build/tests/test

search:
	find ./ -type f -iname '*.gcno'

gcov:
	gcov -abcfu build/string_io/CMakeFiles/string_io.dir/string_io.c.gcno

gcovr:
	rm -rf gcovr_report; mkdir gcovr_report; gcovr -r . --html --html-details -o gcovr_report/coverage.html

install_GTest:
	mkdir gtest 
	cd gtest
	git clone https://github.com/google/googletest.git 
	cd googletest 
	cmake -B build 
	cmake --build build 
	sudo cmake --install build
