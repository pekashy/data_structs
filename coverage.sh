#!/bin/bash
make
./run
lcov -t "run" -o run.info -c -d .
genhtml -o report run.info 
