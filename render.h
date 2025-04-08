#pragma once
#include "render.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

typedef struct {
    int running;
    float window_width;
    float window_height;
} sim_t;

void handle_events(sim_t *sim);
void init_renderer(void);
void draw_plate(float x, float y, float z,
                float nx, float ny, float nz,
                float radius);

void draw(void);
void initOpenGL(float width, float height);

