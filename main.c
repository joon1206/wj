#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>  // Needed for gluPerspective and gluLookAt

#include "render.h"
#include "particle.h"

#define VB_MATH_IMPLEMENTATION
#include "vb.h"

typedef struct {
    int running;
    float window_width;
    float window_height;
} sim_t;

void handle_events(sim_t *sim);
static inline void initOpenGL(float width, float height);
static inline void draw(void);

int main(void) {

    sim_t simulation = {
        .running = 1,
        .window_width = 800.0,  // or get from SDL_GetWindowSize
        .window_height = 600.0,
    };

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("3D Plate Packing",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        simulation.window_width, simulation.window_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    initOpenGL(simulation.window_width, simulation.window_height);

    init_renderer();

    ParticleSystem particles;
    init_ps(&particles);
    draw();


    while (simulation.running) {
        handle_events(&simulation);
        update_ps(&particles);
        draw_ps(&particles);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
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

static inline void initOpenGL(float width, float height)
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

static inline void draw(void)
{
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

