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

inline void initOpenGL(float width, float height)
{
    glewInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, width / height , 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0.0, 5.0, 10.0,   // eye position
            0.0, 0.0, 0.0,    // center of scene
            0.0, 1.0, 0.0     // up vector
    );   

    
    glEnable(GL_DEPTH_TEST);
};

inline void draw(void)
{
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
};
