#! /bin/bash

if [ $# -ne 1 ]; then
	if [ ! -d "build" ]; then
		mkdir build
	fi
	cd build && rm -rf *
	cmake .. && make
	./output
elif [ "$1" == "build" ]; then
	mkdir build && cd build && rm -rf *
	cmake .. && make
	./output
elif [ "$1" == "clean" ]; then
	rm -rf build
else echo"wrong paragram"
fi