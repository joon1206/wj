#include <SDL2/SDL.h>
#include <GL/glew.h>
// #include <GL/glu.h>  // Needed for gluPerspective and gluLookAt

#include "render.h"
#include "particle.h"

#define VB_MATH_IMPLEMENTATION
#include "vb.h"

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
