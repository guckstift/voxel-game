#!/bin/bash

gcc -o voxel-game -ansi -pedantic \
	main.c \
	shader.c \
	memory.c \
	file.c \
	error.c \
	buffer.c \
	matrix.c \
	-lSDL2 -lGLEW -lGL -lm \
