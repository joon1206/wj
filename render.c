#include "render.h"
#include <GL/glu.h>

void init_renderer()
{
    // Placeholder: for now we use immediate mode
}

void draw_plate(float x, float y, float z,
                float nx, float ny, float nz,
                float radius)
{
    const int segments = 20;
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6f, 0.8f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);  // center
    for (int i = 0; i <= segments; i++) {
        float theta = (2.0f * M_PI * i) / segments;
        float dx = radius * cosf(theta);
        float dz = radius * sinf(theta);
        glVertex3f(dx, 0.0f, dz);  // flat in XZ
    }
    glEnd();
    glPopMatrix();
}

void handle_events(sim_t *sim)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            sim->running = 0;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int new_width = event.window.data1;
                int new_height = event.window.data2;
                glViewport(0, 0, new_width, new_height);
                sim->window_width = new_width;
                sim->window_height = new_height;
            }
            break;
        }
    }
}

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
}

inline void draw(void)
{
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
