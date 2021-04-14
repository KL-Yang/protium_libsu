#!/bin/bash

flags="-W -Wall --std=gnu99 -ggdb -O0 -I/home/protium/include/ -L/home/protium/lib"
links="../build/libsu.a -lptcomm"
#gcc $flags test1.c $links -o test1.exe
#gcc $flags test2.c $links -o test2.exe
#gcc $flags test3.c $links -o test3.exe 
gcc $flags test4.c $links -o test4.exe 

