#!/bin/bash

if [ "$1" == rebuild ]; then
	echo rebuild...
	if compgen -G "*.o" > /dev/null; then rm *.o; fi
elif [ "$1" == clean ]; then
	echo clean...
	if compgen -G "*.o" > /dev/null; then rm *.o; fi
	exit 0
else
	echo build...
fi

C_FILES=$(echo *.c)
O_FILES=

for C_FILE in $C_FILES; do
	O_FILE=${C_FILE%.c}.o
	O_FILES="$O_FILES $O_FILE"
	
	if [ $C_FILE -nt $O_FILE ]; then
		echo compile $O_FILE...
		gcc -c -std=c99 -pedantic $C_FILE
		
		if [ $? != 0 ]; then
			echo compile error
			exit 1
		fi
	fi
done

for O_FILE in $O_FILES; do
	if [ $O_FILE -nt "voxel-game" ]; then
		echo link $O_FILES...
		gcc -o voxel-game *.o -lSDL2 -lGLEW -lGL -lm
		
		if [ $? != 0 ]; then
			echo link error
			exit 1
		fi
		
		break
	fi
done
