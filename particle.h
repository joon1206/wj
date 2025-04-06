#pragma once
#include "vb.h"

#define MAX_PARTICLES 128
_Static_assert((MAX_PARTICLES & (MAX_PARTICLES - 1)) == 0,
               "MAX_PARTICLES must be a power of two!");

typedef struct {
  f32 x, y, z;
  f32 nx, ny, nz;
  f32 radius;
} Particle;

typedef struct {
    f32 x[MAX_PARTICLES];
    f32 y[MAX_PARTICLES];
    f32 z[MAX_PARTICLES];
    f32 nx[MAX_PARTICLES];
    f32 ny[MAX_PARTICLES];
    f32 nz[MAX_PARTICLES];
    f32 radius[MAX_PARTICLES];
    u32 count;
} ParticleSystem;

// global ParticleSystem particles;
// global Particle particles[MAX_PARTICLES];

void init_particles(Particle partilces[]);
void update_particles(Particle particles[]);
void draw_particles(Particle particles[]);

void init_ps(ParticleSystem *ps);
void update_ps(ParticleSystem *ps);
void draw_ps(ParticleSystem *ps);
