#!/bin/bash

make;
./Compiler test.dat out.txt > compiler.txt;
gedit compiler.txt;
