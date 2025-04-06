#include "particle.h"
#include "render.h"
#include <stdlib.h>

#define MAX_PARTICLES 100

typedef struct {
    float x, y, z;
    float nx, ny, nz;
    float radius;
} Particle;

static Particle particles[MAX_PARTICLES];

void init_particles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = (rand() % 200 - 100) / 10.0f;
        particles[i].y = (rand() % 200 - 100) / 10.0f;
        particles[i].z = (rand() % 200 - 100) / 10.0f;
        particles[i].nx = 0.0f;
        particles[i].ny = 1.0f;
        particles[i].nz = 0.0f;
        particles[i].radius = 0.5f;
    }
}

void update_particles() {
    // Optional: add movement or interaction logic here
}

void draw_particles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        draw_plate(particles[i].x, particles[i].y, particles[i].z,
                   particles[i].nx, particles[i].ny, particles[i].nz,
                   particles[i].radius);
    }
}
