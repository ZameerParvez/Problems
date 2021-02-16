#! /bin/bash

cmake -S . -B build
cd build || exit
make
