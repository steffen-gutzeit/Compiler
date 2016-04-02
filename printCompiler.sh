#!/bin/bash

make;
./Compiler test.dat out.txt > compiler.txt;
#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./Compiler test.dat out.txt > compiler.txt;
gedit compiler.txt;
