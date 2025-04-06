#include "particle.h"
#include "render.h"
#include "vb.h"
#include <emmintrin.h>
#include <xmmintrin.h>

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

void update_particles(Particle particles[]) { }

void draw_particles(Particle particles[])
{
    for (int i = 0; i < MAX_PARTICLES; i++) 
        draw_plate(particles[i].x, particles[i].y, particles[i].z,
                   particles[i].nx, particles[i].ny, particles[i].nz,
                   particles[i].radius);
    
}

/*
Converts an i32x4 value to a random f32x4 using MurmurHash and Wang Hash mix.
Due to the usage of _mm_mullo_epi32, this requires SSE4 instructions.
*/  
static inline f32x4 hash_f32x4(__m128i x)
{
    x = _mm_xor_si128(x, _mm_srli_epi32(x, 16));
    x = _mm_mullo_epi32(x, _mm_set1_epi32(0x85ebca6b)); // Large prime
    x = _mm_xor_si128(x, _mm_srli_epi32(x, 13));
    x = _mm_mullo_epi32(x, _mm_set1_epi32(0xc2b2ae35)); // Another large prime
    x = _mm_xor_si128(x, _mm_srli_epi32(x, 16));

    // Convert to float and normalize to [-1, 1]
    __m128 fx = _mm_cvtepi32_ps(x);
    const __m128 scale = _mm_set1_ps(1.0f / 2147483648.0f); // 2^31
    return _mm_mul_ps(fx, scale);
}

void init_ps(ParticleSystem* ps)
{
    ps->count = MAX_PARTICLES;
    f32x4 zeros = {0, 0, 0, 0};
    f32x4 ones = {0, 0, 0, 0};
    f32x4 halves = {0.5f, 0.5f, 0.5f, 0.5f};

    for (int i = 0; i < MAX_PARTICLES; i += 4) {
        _mm_storeu_ps(&ps->nx[i], zeros);
        _mm_storeu_ps(&ps->ny[i], ones);
        _mm_storeu_ps(&ps->nz[i], zeros);
        _mm_storeu_ps(&ps->radius[i], halves);


        // NOTE: __vector_size(16) signed_char != __m128i
        __m128i idx = _mm_setr_epi32(i, i+1, i+2, i+3);

        f32x4 randx = hash_f32x4(_mm_add_epi32(idx,  _mm_set1_epi32(0x1234)));
        f32x4 randy = hash_f32x4(_mm_add_epi32(idx,  _mm_set1_epi32(0x5678)));
        f32x4 randz = hash_f32x4(_mm_add_epi32(idx,  _mm_set1_epi32(0x9abc)));

        // Scale to [-10, 10]
        const __m128 scale = _mm_set1_ps(10.0f);
        randx = randx * scale;
        randy = randy * scale;
        randz = randz * scale;

        _mm_storeu_ps(&ps->x[i], randx);
        _mm_storeu_ps(&ps->y[i], randy);
        _mm_storeu_ps(&ps->z[i], randz);
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
