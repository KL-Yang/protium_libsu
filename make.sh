#!/bin/bash

protium make
cd build; rm -rf build; make all; cd ..
#python3 test.py

gcc --std=gnu99 -I/home/protium/include/ -L/home/protium/lib t1.c build/libsu.a -lptcomm -o t1.exe
gcc --std=gnu99 -I/home/protium/include/ -L/home/protium/lib t2.c build/libsu.a -lptcomm -o t2.exe
gcc --std=gnu99 -I/home/protium/include/ -L/home/protium/lib t3.c build/libsu.a -lptcomm -o t3.exe

