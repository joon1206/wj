#!/bin/bash
gcc -Wall -std=c99 main.c render.c particle.c -o plate_sim \
    -lSDL2 -lGL -lGLEW -lm -lGLU -lglut
