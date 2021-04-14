#!/bin/bash

protium make
cd build; rm -rf build; make all; cd ..
#python3 test.py

#note: only if success, should do this!!!
cp build/build/lib.linux-*-3.?/libpysu*.so "$PROTIUM_HOME/pylib/"
cp libsu.h "$PROTIUM_HOME/include/protium/"
cp build/libsu.a "$PROTIUM_HOME/lib"
