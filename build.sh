#! /bin/bash

if [ $# == 1 ]
then
	if [ $1 == "test" ]
	then
		gcc monkeyTyper.c -o build/monkeyTyper
		./monkeyTyper 30
	elif [ $1 == "debug" ]
	then
		gcc -g monkeyTyper.c -o build/monkeyTyperDebug
	fi
else
	gcc monkeyTyper.c -o build/monkeyTyper
fi

