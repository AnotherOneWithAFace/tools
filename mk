#!/bin/sh
filename=${1}
tcc -o ${filename} ${filename}.c
