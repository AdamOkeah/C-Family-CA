#!/bin/bash
gcc -ansi -c msString.c -o msString.o -Wall -g
gcc -ansi -c FullProgram.c -o FullProgram.o -Wall -g


gcc FullProgram.o msString.o -o coursework