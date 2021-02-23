#!/bin/bash

protium make
cd build; rm -rf build; make all; cd ..
#python3 test.py

flags="--std=gnu99 -I/home/protium/include/ -L/home/protium/lib"
links="build/libsu.a -lptcomm"
gcc $flags test1.c $links -o test1.exe
gcc $flags test2.c $links -o test2.exe
gcc --std=gnu99 -I/home/protium/include/ -L/home/protium/lib t3.c build/libsu.a -lptcomm -o t3.exe

