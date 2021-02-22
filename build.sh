#!/bin/bash

C_FILES=$(echo *.c)
O_FILES=

for C_FILE in $C_FILES; do
	O_FILE=${C_FILE%.c}.o
	O_FILES="$O_FILES $O_FILE"
	
	if [ $C_FILE -nt $O_FILE ]; then
		echo compile $O_FILE
		gcc -c -ansi -pedantic $C_FILE
	fi
done

echo link $O_FILES
gcc -o voxel-game -ansi -pedantic *.o -lSDL2 -lGLEW -lGL -lm
