#include "particle.h"
#include "render.h"
#include "vb.h"

void init_particles(Particle particles[])
{
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

void init_ps(ParticleSystem* ps)
{
    ps->count = MAX_PARTICLES;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        ps->x[i] = (rand() % 200 - 100) / 10.0f;
        ps->y[i] = (rand() % 200 - 100) / 10.0f;
        ps->z[i] = (rand() % 200 - 100) / 10.0f;

        ps->nx[i] = 0.0f;
        ps->ny[i] = 1.0f;
        ps->nz[i] = 0.0f;

        ps->radius[i] = 0.5f;
    }
}

void update_particles(Particle particles[])
{

}

void draw_particles(Particle particles[])
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        draw_plate(particles[i].x, particles[i].y, particles[i].z,
                   particles[i].nx, particles[i].ny, particles[i].nz,
                   particles[i].radius);
    }
}

void update_ps(ParticleSystem *ps) {}

void draw_ps(ParticleSystem *ps)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        draw_plate(
            ps->x[i], ps->y[i], ps->z[i],
            ps->nx[i], ps->ny[i], ps->nz[i],
            ps->radius[i]
        );
    }
}
