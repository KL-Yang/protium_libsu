#!/bin/bash

flags="-W -Wall --std=gnu99 -ggdb -O0 -I/home/protium/include/ -L/home/protium/lib"
links="../build/libsu.a -lptcomm"

if [ "$#" -lt 1 ]; then
    echo "Usage: ./make.sh test_id"
    echo "  test_id=0 to run all test!"
    exit
fi

if [ "$1" -eq 1 ] || [ "$1" -eq 0 ]; then
    echo "# compile-1"
    gcc $flags test1.c $links -o test1.exe
    ./test1.exe wav.su wav_test1c.su
    ./test1.py wav.su wav_test1py.su
fi

if [ "$1" -eq 2 ] || [ "$1" -eq 0 ]; then
    echo "# compile-2"
    gcc $flags test2.c $links -o test2.exe
    ./test2.exe model_cp.su model_test2c.su
    ./test2.py model_cp.su model_test2py.su
fi
exit
gcc $flags test3.c $links -o test3.exe 
./test3.exe
gcc $flags test4.c $links -o test4.exe 

