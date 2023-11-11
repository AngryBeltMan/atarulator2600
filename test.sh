#!/bin/sh
gcc -Wall -Wextra -o tests.out tests/run_tests.c -g
echo Running tests
./tests.out

