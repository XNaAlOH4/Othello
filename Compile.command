#!/bin/bash

printf "Enter Name of C File: "

read in

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)"

/usr/local/Cellar/gcc/HEAD-8e62038/bin/c++-HEAD -shared -o $DIR/$in.o $DIR/$in.c

clang -shared $DIR/$in.o -o $DIR/$in.dylib
