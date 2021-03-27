#!/bin/bash

printf "Type in file name: "
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)"
read in

/usr/local/Cellar/gcc/HEAD-8e62038/bin/c++-HEAD $DIR/$in.cpp

##mv $DIR/a.out $DIR/$in