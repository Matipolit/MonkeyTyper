#! /bin/bash

if [ $# == 1 ]
then
	if [ $1 == "test" ]
	then
		mkdir build
		gcc monkeyTyper.c -o build/monkeyTyper
		./monkeyTyper 30
	elif [ $1 == "debug" ]
	then
		mkdir build
		gcc -g monkeyTyper.c -o build/monkeyTyperDebug
	fi
else
	mkdir build
	gcc monkeyTyper.c -o build/monkeyTyper
fi

