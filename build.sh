#!/bin/bash

WFLAGS="-Wall -Wextra -pedantic"
CFLAGS="-msse4 -O3 -ffast-math -ffinite-math-only"
LIBS="-lm -lSDL2 -lGLU -lGLEW -lGL"
SRC="main.c particle.c render.c"
OUT="plate_sim"

echo "Building $OUT..."
gcc $SRC -o $OUT $CFLAGS $LIBS

if [ $? -eq 0 ]; then
    echo "Build succeeded: ./$OUT"
else
    echo "Build failed."
fi
